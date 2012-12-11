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



//TODO: For event system, we have the sender id! We can message back if a message fails - you should utilise this feature....
//TODO: Need a feature to monitor bolt-ons like what guns a ship has etc and how long they have left (just a bit field thing would do) as a component? Would help with powerups too

//Search for "//@@@Requires updating on addition on new subsystem" when adding new subsystems"
int main()
{

    std::cout.setstate(std::ios::failbit);

    Core core("coreConfig.xml");
    ObjectId playerId = core.getObjectBuilder()->createObject("player");
    core.getObjectBuilder()->createObject("simpleBullet");
    core.getObjectBuilder()->createObject("coin");
    core.getObjectBuilder()->createObject("livingQuarters");
    core.getObjectBuilder()->createObject("speedPowerUp");

    NamedParams params;
    params["Anchor"]="true";
    std::stringstream parentId("");
    parentId << playerId;
    params["Object.Anchor.Parent"]=parentId.str();

    //first gun
    int xOffset = core.getCoordsSub()->getComponent(playerId)->getDimensions().x/2;
    int x = -40 - xOffset;
    std::stringstream ss("");
    ss << x;
    params["Object.Anchor.Offset.x"]="40"; ;
    params["Object.Anchor.Offset.y"]="0";
    ObjectId gun1id = core.getObjectBuilder()->createObject("gun",params);

    //second gun
    params["Object.Anchor.Offset.x"]=ss.str();
    ObjectId gun2id = core.getObjectBuilder()->createObject("gun",params);

    //rear gun
    std::stringstream ss2("");
    ss2 << 0 - xOffset;
    params["Object.Anchor.Offset.x"]=ss2.str();
    params["Object.Anchor.Offset.y"]="40";
    ObjectId gun3id = core.getObjectBuilder()->createObject("rearGun",params);

    TriggerComp* playerTriggerComp = core.getTriggerSub()->getComponent(playerId);
    playerTriggerComp->addReceiverObject("guns",gun1id);
    playerTriggerComp->addReceiverObject("guns",gun2id);
    playerTriggerComp->addReceiverObject("guns",gun3id);

    core.getUi()->setPlayer(playerId);


    double elapsed;
    bool firstRun = true;
    int count = 0;
    double totElapsed =0.0;
  //  clock_t startTime = clock();


    MusicPlayer mPlayer(&core);
    mPlayer.loadMusic("grime.wav");
    sf::Clock fpsClock;
    double startTime = fpsClock.GetElapsedTime();
    fpsClock.Reset();

//    mPlayer.loadMusic("grime.wav");
    mPlayer.play();

    double spareTime = 0;
    float fps = 20.0;
    double totTime = 0.0;
    while(firstRun==true)
    {

        elapsed = fpsClock.GetElapsedTime();

        fpsClock.Reset();
        totTime+=elapsed;
        std::cerr << "tot: " << totTime << std::endl;
//        if(elapsed < 1.0/fps)
//        {
//            sf::Sleep(1.0/fps - elapsed);
//            spareTime+=(1.0/fps - elapsed);
//            std::cout << "Sleeping: " << 1.0/fps - elapsed << "\t" << spareTime << std::endl;
//
//        }





        //update music player
        mPlayer.update(elapsed);
        //update messageCentre
        core.getMessageCentre()->update(elapsed);

        //deliver messages
        core.getEffectsSub()->deliverAllMessages();
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
        core.getTriggerSub()->deliverAllMessages();
        core.getStatsSub()->deliverAllMessages();
        core.getObjectStore()->deliverAllMessages();

        //update subsystems
//        core.getInputSub()->update(elapsed);
        core.getEffectsSub()->update(elapsed);
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
        core.getStatsSub()->update(elapsed);
        core.getTriggerSub()->update(elapsed);

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



