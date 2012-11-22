#include "Systems.h"
#include "Core.h"
#include "AiComp.h"
#include <iostream>
#include "Goal.h"

template <>
void System<AiComp>::update(double elapsed)
{

    std::map<ObjectId,AiComp>::iterator iCom = components_.begin();



}



template <>
void System<AiComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to AiComps" << std::endl;
    //check if target entity is registered with this subsystem
    AiComp* targetComponent = getComponent(message.getTargetId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];

//    if (mainCmd=="play")
//    {
//        //get sound corresponding to key
//        std::string key = params[2];
//        SoundManager* soundManager = static_cast<SoundManager*>(extensions_);
//        soundManager->playSound(targetComponent->getSound(key));
//        std::cout << "PLAYING A SOUND!" << std::endl;
//    }




}


template <>
void System<AiComp>::init()
{

}

