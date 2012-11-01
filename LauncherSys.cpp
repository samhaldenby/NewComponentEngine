#include "Systems.h"
#include "LauncherComp.h"
#include <iostream>
#include "Core.h"
#include "Telegram.h"
#include "Message.h"
#include "MessageCentre.h"

template <>
void System<LauncherComp>::update(double elapsed)
{
//    std::cout << "Updating HealthComp" << std::endl;

    //update all health components
    std::multimap<ObjectId,LauncherComp>::iterator iCom = components_.begin();
    while(iCom!=components_.end())
    {
        LauncherComp* currComponent = &iCom->second;

        //reduce cooldowns
        if(currComponent->isOnCooldown())
        {
            currComponent->reduceCooldownBy(elapsed);

            //check if cooldown completed
            if(currComponent->getCurrCooldown()<=0)
            {
                currComponent->setCurrCooldown(0.0);
//                currComponent->reduceCoolDownBy(coolDown + currComponent->getMaxCooldown());
                currComponent->setOnCooldown(false);
            }
        }



        ++iCom;
    }
}


template <>
void System<LauncherComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to LauncherComps" << std::endl;
    //check if target entity is registered with this subsystem
    LauncherComp* targetComponent = getComponent(message.getSourceId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];

    if (mainCmd=="setMaxCooldown")
    {
        targetComponent->setMaxCooldown(atof(params[2].c_str()));
    }
    else if (mainCmd=="launch")
    {
        if(!targetComponent->isOnCooldown())
        {
            //launch
            //create telegram for shooting a bullet
            ObjectId bulletId = core_->getObjectBuilder()->createObject(targetComponent->getProjectileBlueprintName());
            Parameters changePosParams;
            changePosParams.push_back("coords");
            changePosParams.push_back("setCoords");
            std::stringstream xSS(""), ySS("");
            CoordsComp* launcherCoordsComp = core_->getCoordsSub()->getComponent(message.getSourceId());
            xSS << launcherCoordsComp->getCoords().x + launcherCoordsComp->getDimensions().x/2 ;
            ySS << launcherCoordsComp->getCoords().y;
            changePosParams.push_back(xSS.str());
            changePosParams.push_back(ySS.str());
            Message changePosMessage(bulletId, bulletId, changePosParams);
            Telegram changePosTelegram(bulletId, bulletId, 0.0, changePosMessage);

            //send messages
            core_->getMessageCentre()->addTelegram(changePosTelegram);

            //put on cooldown
            targetComponent->setOnCooldown(true);
            targetComponent->setCurrCooldown(targetComponent->getMaxCooldown());

        }


    }


}
