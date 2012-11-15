#include "AiManager.h"
#include "GoalBuilders.h"
#include "Utils.h"
#include <map>

AiManager::AiManager(Core* core)
{
    core_ = core;
    Goal::setCore(core);
    initGoalMakerFunctions_();
}


Core* AiManager::getCore()
{
    return core_;
}


void AiManager::initGoalMakerFunctions_()
{
    goalMakerFnMap_["run"]= &makeMoveGoal;
    goalMakerFnMap_["wait"]=&makeWaitGoal;
}

Goal* AiManager::parseGoalString(std::string command)
{
    //first, create a map to store temp goals in
    std::map<char,Goal* > goalMap;

    //split by ;
    StrTokens subCmd = tokenise(command,';');

    //process each command
    StrTokens::iterator iSub = subCmd.begin();
    while(iSub!=subCmd.end())
    {
        //find the '=' and grab the character before it
        int eqPos = iSub->find('=');
        char key= (*iSub)[eqPos-1];

        StrTokens goalToks = tokenise(iSub->substr(eqPos+1),',');
        StrTokens::iterator iGT = goalToks.begin();

        std::list<Goal*> goalList;
        while(iGT!=goalToks.end())
        {
            //split into Params
            StrTokens args = tokenise(*iGT, ' ');

            //check if it's a $ variable
            Goal* g;
            if (args[0][0]=='$')
            {
                char findKey = args[0][1];
                g = goalMap[findKey];
            }
            else
            {
                g = goalMakerFnMap_[args[0]](args);
            }
            std::cout << key << "\t" << *iGT << std::endl;

            goalList.push_back(g);

            ++iGT;

        }

        //check how many goals were in there.
        if (goalList.size()>1)
        {
            goalMap[key] = new GoalGroup(goalList);
        }
        else
        {
            goalMap[key] = goalList.front();
        }

        ++iSub;
    }

    return goalMap['%'];
}



