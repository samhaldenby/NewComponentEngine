#include <iostream>
#include <vector>

#include "Core.h"

#include "Systems.h"
#include "MessageCentre.h"
#include "HealthComp.h"
#include "NameComp.h"


//Search for "//@@@Requires updating on addition on new subsystem" when adding new subsystems"
int main()
{
    Core core("coreConfig.xml");

    core.getObjectBuilder()->createObject("player");
    core.getObjectBuilder()->createObject("simpleBullet");
    core.getObjectBuilder()->createObject("coin");
    core.getObjectBuilder()->createObject("livingQuarters");



    int dump;
//    std::cin >> dump;
    double elapsed;
    bool firstRun = true;
//    int count = 0;
//    double totElapsed =0.0;
  //  clock_t startTime = clock();
    while(firstRun==true)
    {
        //update messageCentre
        core.getMessageCentre()->update(elapsed);

        //deliver messages
        core.getMoveSub()->deliverAllMessages();
        core.getHealthSub()->deliverAllMessages();
        core.getNameSub()->deliverAllMessages();
        core.getGfxSub()->deliverAllMessages();
        //update subsystems
//        core.getInputSub()->update(elapsed);
        core.getMoveSub()->update(elapsed);
//        core.getGfxSub()->update(elapsed);
        core.getHealthSub()->update(elapsed);
        core.getNameSub()->update(elapsed);
        core.getGfxSub()->update(elapsed);
        firstRun = true;
//        elapsed=clock() - startTime;
//        ++count;
//        totElapsed+=elapsed;

//        count++;
//        std::cout << count << std::endl;
    }


    return 0;
}



