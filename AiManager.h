#ifndef AIMANAGER_H_INCLUDED
#define AIMANAGER_H_INCLUDED

#include "Goal.h"
#include "TypeDefs.h"
#include <string>
#include <map>


typedef Goal* (*GoalMakerFn)(Parameters);
typedef std::map<std::string,GoalMakerFn> GoalMakerFnMap;

class Core;

class AiManager
{
    public:
        AiManager(Core* core);
        Goal* parseGoalString(std::string goalStr);
        Core* getCore();

    private:
        void initGoalMakerFunctions_();
        Core* core_;
        GoalMakerFnMap goalMakerFnMap_;

};

#endif // AIMANAGER_H_INCLUDED
