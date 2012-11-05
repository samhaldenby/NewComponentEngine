#include "Systems.h"
#include "Core.h"
#include "AudioComp.h"
#include "Ui.h"
#include <iostream>


template <>
void System<AudioComp>::update(double elapsed)
{

    std::map<ObjectId,AudioComp>::iterator iCom = components_.begin();



}



template <>
void System<AudioComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to AudioComps" << std::endl;
    //check if target entity is registered with this subsystem
    AudioComp* targetComponent = getComponent(message.getTargetId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];

//    if (mainCmd=="changeSprite")
//    {
//        targetComponent->setSprite(core_->getStore()->getImage(params[2]));
////        targetComponent->setLocalDestination(Vector2d(atoi(params[2].c_str()),atoi(params[3].c_str())));
//    }
//
//    else if (mainCmd=="changeCurrBy")
//    {
//        targetComponent->setCurrent(targetComponent->getCurrent() + atoi(params[2].c_str()));
//    }


}
