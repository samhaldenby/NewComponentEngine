#include "Systems.h"
#include "HealthComp.h"
#include "Telegram.h"
#include "Message.h"
#include "MessageCentre.h"
#include "Core.h"
#include <iostream>

template <>
void System<HealthComp>::update(double elapsed)
{
//    std::cout << "Updating HealthComp" << std::endl;

    //update all health components
    std::multimap<ObjectId,HealthComp>::iterator iCom = components_.begin();
    while(iCom!=components_.end())
    {
        HealthComp* currComponent = &iCom->second;

        //ensure current health is in bound
        if(currComponent->getCurrent() > currComponent->getMax())
        {
            currComponent->setCurrent(currComponent->getMax());
        }

        if(currComponent->getCurrent() <= 0)
        {
            //grab on zero health messages
            std::vector<Parameters> zeroMessages = currComponent->getOnZeroHealthMessages();
            for (int x=0; x< zeroMessages.size();++x)
            {

                Message msg(currComponent->getId(),currComponent->getId(), zeroMessages[x]);
                Telegram telegram(currComponent->getId(), currComponent->getId(), 0.0, msg);
                core_->getMessageCentre()->addTelegram(telegram);
            }
        }

        ++iCom;
    }
}


template <>
void System<HealthComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to HealthComps" << std::endl;
    //check if target entity is registered with this subsystem
    HealthComp* targetComponent = getComponent(message.getTargetId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];

    if (mainCmd=="changeMaxBy")
    {
        targetComponent->setMax(targetComponent->getMax() + atoi(params[2].c_str()));
    }

    else if (mainCmd=="changeCurrBy")
    {
        targetComponent->setCurrent(targetComponent->getCurrent() + atoi(params[2].c_str()));
        std::cout << "Health is now " << targetComponent->getCurrent() << " / " << targetComponent->getMax() << std::endl;
    }

    else if (mainCmd=="changeMaxTo")
    {
        targetComponent->setMax(atoi(params[2].c_str()));
    }

    else if (mainCmd=="changeCurrTo")
    {
        targetComponent->setCurrent(atoi(params[2].c_str()));
    }

    else if (mainCmd=="restoreToMax")
    {
        targetComponent->setCurrent(targetComponent->getMax());
    }

//    if(mainCmd=="change")
//    {
//        targetComponent->setSprite(params[2]);
//    }
}
