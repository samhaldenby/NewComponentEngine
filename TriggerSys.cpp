#include "Systems.h"
#include "Core.h"
#include "TriggerComp.h"
#include "Ui.h"
#include "Telegram.h"
#include "MessageCentre.h"
#include <iostream>


template <>
void System<TriggerComp>::update(double elapsed)
{

    std::map<ObjectId,TriggerComp>::iterator iCom = components_.begin();


}



template <>
void System<TriggerComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to TriggerComps" << std::endl;
    //check if target entity is registered with this subsystem
    TriggerComp* targetComponent = getComponent(message.getTargetId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];


    if (mainCmd=="activate")
    {
        std::string activationTag = params[2];


        std::vector<ObjectId> ids = targetComponent->getTriggeredObjects(activationTag);
        std::vector<Parameters> trigParams = targetComponent->getTriggeredParameters(activationTag);
        std::cout << "There are " << ids.size() << " target objects for '" << activationTag << "' tag" << std::endl;
        std::vector<ObjectId>::iterator iId = ids.begin();
        while(iId!=ids.end())
        {
            //check if target object exists. If not, remove it from tagged ObjectList
            if(core_->getObjectStore()->getObject(*iId)==NULL)
            {
                targetComponent->removeReceiverObject(*iId);
                continue;
                ++iId;
            }
            else
            {
                std::cout << "Processing message for object "<< *iId << std::endl;
                //for each set of message params, send a message
                std::vector<Parameters>::iterator iParams = trigParams.begin();
                while(iParams != trigParams.end())
                {
                    //bundle message and send it
                    Message trigMsg(message.getTargetId(), *iId, *iParams);
                    Telegram trigTelegram(message.getTargetId(), *iId,0.0, trigMsg);
                    core_->getMessageCentre()->addTelegram(trigTelegram);
                    ++iParams;
                }
                ++iId;
            }

        }
    }

}


template <>
void System<TriggerComp>::init()
{

}
