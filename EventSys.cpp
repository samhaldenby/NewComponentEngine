#include "Systems.h"
#include "Core.h"
#include "EventComp.h"
#include "Telegram.h"
#include "MessageCentre.h"
//#include "Ui.h"
//#include "SoundManager.h"
#include <iostream>


template <>
void System<EventComp>::update(double elapsed)
{

//    std::map<ObjectId,EventComp>::iterator iCom = components_.begin();
//
//    //ensure there are initialised audios available
//    if (this->extensions_==NULL)
//    {
//        std::cout << "No audios initialised. Will create now" << std::endl;
//        extensions_ = new SoundManager();
//        SoundManager* soundManager = static_cast<SoundManager*>(extensions_);
//    }


}



template <>
void System<EventComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to EventComps" << std::endl;
    //check if target entity is registered with this subsystem
    std::cout << "Now searching for component target " << message.getTargetId() << std::endl;
    std::cout << "Now searching for component source " << message.getSourceId() << std::endl;
    EventComp* targetComponent = getComponent(message.getTargetId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];

    if (mainCmd=="execute")
    {
        //get key
        std::string key = params[2];
        std::vector<Parameters>* message = targetComponent->getEvents(key);
        if (message!=NULL)
        {
            for (int x=0; x< message->size(); ++x)
            {
                //send message
    //            ObjectId bulletId = core_->getObjectBuilder()->createObject(targetComponent->getProjectileBlueprintName());
    //            Parameters changePosParams;
    //            changePosParams.push_back("coords");
    //            changePosParams.push_back("setCoords");
    //            std::stringstream xSS(""), ySS("");
    //            CoordsComp* launcherCoordsComp = core_->getCoordsSub()->getComponent(message.getTargetId());
    //            xSS << launcherCoordsComp->getCoords().x + launcherCoordsComp->getDimensions().x/2 ;
    //            ySS << launcherCoordsComp->getCoords().y-10;
    //            changePosParams.push_back(xSS.str());
    //            changePosParams.push_back(ySS.str());
                Message msg(targetComponent->getId(), targetComponent->getId(), (*message)[x]);
                Telegram tel(targetComponent->getId(), targetComponent->getId(), 0.0, msg);
                core_->getMessageCentre()->addTelegram(tel);
            }
        }

    }
//    if (mainCmd=="play")
//    {
//        //get sound corresponding to key
//        std::string key = params[2];
//        SoundManager* soundManager = static_cast<SoundManager*>(extensions_);
//        soundManager->playSound(targetComponent->getSound(key));
//        std::cout << "PLAYING A SOUND!" << std::endl;
//    }
}
