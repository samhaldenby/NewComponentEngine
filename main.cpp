#include <iostream>
#include <vector>

#include "Core.h"
#include "Utils.h"

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
    srand(time(NULL));
    int w=200;
    int h=150;
    int steps = 50;

    //test for catmull

    Vector2d p0(rand()%w,rand()%h);
    Vector2d p1(rand()%w,rand()%h);
    Vector2d p2(rand()%w,rand()%h);
    Vector2d p3(rand()%w,rand()%h);

    std::ofstream out;
    out.open("catmull.txt");

    for (int c=0; c<5; ++c)
    {
        Vector2d next(rand()%w,rand()%h);
        Vector2d next2(rand()%w,rand()%h);
        //works ok - quite roundy
//        p0=p1;
//        p1=p2;
//        p2=p3;
//        p3=next;
        //works ok - more jaggedy
        p0=p1;
        p1=p2;
        p2=next;
        p3=next2;

        for (int x=0;x<steps;++x)
        {
            float t = x/float(steps);
            Vector2d r = calculateCatmullPoint(t,p0,p1,p2,p3);
            if(x==0)
            {
                out << r.x << "\t" << r.y << "\t" << r.x << "\t" << r.y << std::endl;
            }
            else
            {
                 out << r.x << "\t" << r.y << "\t" << std::endl;
            }
        }
    }

    out.close();
    //end test for catmull
    //test for bezier curving

//    int minDist = sqrt(h/2 *h/2 + w/2 * w/2) * 0.5;
//    std::cout << "MinDist: " << minDist << std::endl;
//    Vector2d start(rand()%w,0);
//    Vector2d end(rand()%w,h);
//    std::ofstream out;
//    out.open("bezier.txt");
//    for (int c=0;c<3;++c)
//    {
//
//        Vector2d p0 = start;
//        Vector2d p1(rand()%w,rand()%h);
//        Vector2d p2(rand()%w,rand()%h);
//        Vector2d p3(rand()%w,rand()%h);
//        while(p3.getDistance(p1)<minDist)
//        {
//            p3.x = rand()%w;
//            p3.y = rand()%h;
//        }
//
//        for (int x=0; x<steps;++x)
//        {
//            float t = x/float(steps);
//            Vector2d res= calculateBezierPoint(t,p0,p1,p2,p3);
//            if (x!=0)
//            {
//                out << t << "\t" << res.x <<"\t" << res.y << std::endl;
//            }
//            else
//            {
//                out << t << "\t" << res.x <<"\t" << res.y << "\t" << start.x << "\t" << start.y << std::endl;
//            }
//        }
//
//        start = p3;
//    }
//
//    //do last link
//    Vector2d p0 = start;
//    Vector2d p1(rand()%w,rand()%h);
//    Vector2d p2(rand()%w,rand()%h);
//    Vector2d p3 = end;
//    for (int x=0; x<steps;++x)
//    {
//        float t = x/float(steps);
//        Vector2d res= calculateBezierPoint(t,p0,p1,p2,p3);
//        if (x!=0)
//        {
//            out << t << "\t" << res.x <<"\t" << res.y << std::endl;
//        }
//        else
//        {
//            out << t << "\t" << res.x <<"\t" << res.y << "\t" << start.x << "\t" << start.y << std::endl;
//        }
//    }
//
//
//
//
//    out.close();
//
    //end test for bezier curving

    return 1;

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
//        std::cerr << "tot: " << totTime << std::endl;
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



