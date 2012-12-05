#include "Telegram.h"
#include "Message.h"
#include "Object.h"
#include "Core.h"
#include "ObjectStore.h"

#include "Systems.h"
#include <iostream>

Core* Telegram::core_ = NULL;

void Telegram::setCore(Core* core)
{
    core_ = core;
}



Telegram::Telegram(ObjectId sender, ObjectId receiver, double timeUntilDispatch, Message message) : sender_(sender_) , receiver_(receiver) , timeUntilDispatch_(timeUntilDispatch) , message_(message)
{

}




void Telegram::reduceTime(double elapsed)
{
    timeUntilDispatch_-=elapsed;
}



bool Telegram::isValid()
{
    //check target exists
    Object* targetObject = NULL;
    targetObject = core_->getObjectStore()->getObject(receiver_);

    if(targetObject)
    {
        return true;
    }

    return false;
}


//@@@Requires updating on addition on new subsystem
void Telegram::sendMessage()
{
//    std::cout << "Implement Telegram::sendMessage()" << std::endl;
    //TODO: if this is to remain as an if/else set up, ensure that you put the most frequently used ones at the top of chain
    //Prob best implemented as hash_map of object function pointers
    std::cout << "Telegram::sendMessage()" << std::endl;
    std::string targetSub = message_.getParameters()[0];
    std::cout << "->" <<  targetSub;
    for (int x=0; x<message_.getParameters().size(); ++x)
    {
        std::cout << message_.getParameters()[x] << " ";
    }
    std::cout << std::endl;
    if (targetSub=="health") core_->getHealthSub()->addMessage(message_);
    else if (targetSub=="name") core_->getNameSub()->addMessage(message_);
    else if (targetSub=="coords") core_->getCoordsSub()->addMessage(message_);
    else if (targetSub=="move") core_->getMoveSub()->addMessage(message_);
    else if (targetSub=="gfx") core_->getGfxSub()->addMessage(message_);
    else if (targetSub=="ai") core_->getAiSub()->addMessage(message_);
    else if (targetSub=="anchor") core_->getAnchorSub()->addMessage(message_);
    else if (targetSub=="event") core_->getEventSub()->addMessage(message_);
    else if (targetSub=="audio") core_->getAudioSub()->addMessage(message_);
    else if (targetSub=="launcher") core_->getLauncherSub()->addMessage(message_);
    else if (targetSub=="collision") core_->getCollisionSub()->addMessage(message_);
    else if (targetSub=="object") core_->getObjectStore()->addMessage(message_);
    else if (targetSub=="stats") core_->getStatsSub()->addMessage(message_);
    else if (targetSub=="trigger") core_->getTriggerSub()->addMessage(message_);

}


bool Telegram::readyForDispatch()
{
    return (timeUntilDispatch_ <= 0);
}
