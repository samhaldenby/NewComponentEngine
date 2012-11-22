#include "Systems.h"
#include "Core.h"
#include "AudioComp.h"
#include "Ui.h"
#include "SoundManager.h"
#include <iostream>


template <>
void System<AudioComp>::update(double elapsed)
{

    std::map<ObjectId,AudioComp>::iterator iCom = components_.begin();

    //ensure there are initialised audios available
//    if (this->extensions_==NULL)
//    {
//        std::cout << "No audios initialised. Will create now" << std::endl;
//
//    }


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

    if (mainCmd=="play")
    {
        //get sound corresponding to key
        std::string key = params[2];
        SoundManager* soundManager = static_cast<SoundManager*>(extensions_);
        soundManager->playSound(targetComponent->getSound(key));
        std::cout << "PLAYING A SOUND!" << std::endl;
    }

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


template <>
void System<AudioComp>::init()
{
    extensions_ = new SoundManager();
    SoundManager* soundManager = static_cast<SoundManager*>(extensions_);
    soundManager->loadMusic("ith.wav");
    soundManager->analyseMusic();
}
