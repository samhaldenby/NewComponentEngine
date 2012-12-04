#include <iostream>
#include <vector>

#include "Core.h"

#include "Systems.h"
#include "MessageCentre.h"
#include "HealthComp.h"
#include "NameComp.h"
#include "Ui.h"
#include "Telegram.h"

#include "MusicPlayer.h"



//Search for "//@@@Requires updating on addition on new subsystem" when adding new subsystems"
int main()
{
//    std::cout.setstate(std::ios::failbit);
    Core core("coreConfig.xml");
    ObjectId playerId = core.getObjectBuilder()->createObject("player");
    core.getObjectBuilder()->createObject("simpleBullet");
    core.getObjectBuilder()->createObject("coin");
    core.getObjectBuilder()->createObject("livingQuarters");

    NamedParams params;
    params["Anchor"]="true";
    std::stringstream parentId("");
    parentId << playerId;
    params["Object.Anchor.Parent"]=parentId.str();
    params["Object.Anchor.Offset.x"]="30";
    params["Object.Anchor.Offset.y"]="0";
    core.getObjectBuilder()->createObject("coin",params);

    params["Object.Anchor.Offset.x"]="-30";
    core.getObjectBuilder()->createObject("coin",params);


    core.getUi()->setPlayer(playerId);


    double elapsed;
    bool firstRun = true;
    int count = 0;
    double totElapsed =0.0;
  //  clock_t startTime = clock();
    sf::Clock fpsClock;
    double startTime = fpsClock.GetElapsedTime();

    MusicPlayer mPlayer(&core);
    mPlayer.loadMusic("grime.wav");
    mPlayer.play();

    double spareTime = 0;
    float fps = 60.0;
    while(firstRun==true)
    {

        elapsed = fpsClock.GetElapsedTime();
//        if(elapsed < 1.0/fps)
//        {
//            sf::Sleep(1.0/fps - elapsed);
//            spareTime+=(1.0/fps - elapsed);
//            std::cout << "Sleeping: " << 1.0/fps - elapsed << "\t" << spareTime << std::endl;
//
//        }




        fpsClock.Reset();

        //update music player
        mPlayer.update(elapsed);
        //update messageCentre
        core.getMessageCentre()->update(elapsed);

        //deliver messages
        core.getMoveSub()->deliverAllMessages();
        core.getHealthSub()->deliverAllMessages();
        core.getNameSub()->deliverAllMessages();
        core.getAnchorSub()->deliverAllMessages();
        core.getCoordsSub()->deliverAllMessages();
        core.getGfxSub()->deliverAllMessages();
        core.getAudioSub()->deliverAllMessages();
        core.getAiSub()->deliverAllMessages();
        core.getEventSub()->deliverAllMessages();
        core.getLauncherSub()->deliverAllMessages();
        core.getCollisionSub()->deliverAllMessages();
        core.getObjectStore()->deliverAllMessages();

        //update subsystems
//        core.getInputSub()->update(elapsed);
        core.getAnchorSub()->update(elapsed);
        core.getMoveSub()->update(elapsed);
//        core.getGfxSub()->update(elapsed);
        core.getHealthSub()->update(elapsed);
        core.getNameSub()->update(elapsed);
        core.getLauncherSub()->update(elapsed);
        core.getGfxSub()->update(elapsed);
        core.getAudioSub()->update(elapsed);
        core.getAiSub()->update(elapsed);
        core.getEventSub()->update(elapsed);
        core.getCollisionSub()->update(elapsed);

        firstRun = true;
//        elapsed=clock() - startTime;
        ++count;
        totElapsed+=elapsed;

//        count++;
//        std::cout << count << std::endl;

        core.getUi()->update(elapsed);
        if (totElapsed > 1.0)
        {
//            ObjectId newObjId = core.getObjectBuilder()->createObject("livingQuarters");
            {
//                Parameters changePosParams;
//                changePosParams.push_back("coords");
//                changePosParams.push_back("setCoords");
//                std::stringstream xSS(""), ySS("");
//                xSS << rand()%800;
//                ySS << rand()%600;
//                changePosParams.push_back(xSS.str());
//                changePosParams.push_back(ySS.str());
//                Message changePosMessage(newObjId, newObjId, changePosParams);
//                Telegram changePosTelegram(newObjId, newObjId, 0.0, changePosMessage);
//                core.getMessageCentre()->addTelegram(changePosTelegram);
            }
            std::cout << "Count: " << count << std::endl;
            totElapsed-=1.0;
            count = 0;
        }
        //        std::cout << "Elapsed this frame: " << elapsed << std::endl;



    }


    return 0;
}



