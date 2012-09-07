#include "Systems.h"
#include "CollisionComp.h"
#include <iostream>
#include "Core.h"
#include "Telegram.h"
#include "Message.h"
#include "MessageCentre.h"

template <>
void System<CollisionComp>::update(double elapsed)
{
//    std::cout << "Updating HealthComp" << std::endl;

    //update all health components
    std::multimap<ObjectId,CollisionComp>::iterator iCom = components_.begin();
    while(iCom!=components_.end())
    {
        CollisionComp* currComponent = &iCom->second;



        ++iCom;
    }
}


template <>
void System<CollisionComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to LauncherComps" << std::endl;
    //check if target entity is registered with this subsystem
    CollisionComp* targetComponent = getComponent(message.getSourceId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];

//    if (mainCmd=="setMaxCooldown")
//    {
//        targetComponent->setMaxCooldown(atof(params[2].c_str()));
//    }



}
