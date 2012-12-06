#include "Systems.h"
#include "Core.h"
#include "EffectsComp.h"
#include "Ui.h"
#include "Telegram.h"
#include "MessageCentre.h"
#include <iostream>


template <>
void System<EffectsComp>::update(double elapsed)
{

    std::map<ObjectId,EffectsComp>::iterator iCom = components_.begin();

    while(iCom!=components_.end())
    {
        EffectsComp* effectsComp = &iCom->second;
        EffectsMap* effectsMap = effectsComp->getEffects();
        std::cout << "Address of effectsMap: "<< effectsMap << std::endl;
        std::cout << "copy of effects map size : "<< effectsMap->size() << std::endl;
        std::cout << "orig effects map size : " << effectsComp->getEffects()->size() << std::endl;
        //update each effect in component as necessary
        EffectsMap::iterator iEffect = effectsMap->begin();
        while(iEffect!=effectsMap->end())
        {
            //only update if active
            if(iEffect->second->isActive())
            {
                 //update timer if necessary
                if(iEffect->second->hasDuration())
                {
                    iEffect->second->updateDuration(elapsed);
                    //check if timer has expired
                    if (iEffect->second->hasExpired())
                    {
                        //do on end messages
                        std::vector<Parameters> endParams = iEffect->second->getOnEnd();
                        std::vector<Parameters>::iterator iParams = endParams.begin();
                        while(iParams!= endParams.end())
                        {
                            Message msg(effectsComp->getId(), effectsComp->getId(), *iParams);
                            Telegram tel(effectsComp->getId(), effectsComp->getId(), 0.0, msg);
                            core_->getMessageCentre()->addTelegram(tel);
                            ++iParams;
                        }

                        //delete params
                        effectsMap->erase(iEffect++);
                    }

                }

                //carry out onUpdate messages
                std::vector<Parameters> updateParams = iEffect->second->getOnUpdate();
                std::vector<Parameters>::iterator iParams = updateParams.begin();
                while(iParams!= updateParams.end())
                {
                    Message msg(effectsComp->getId(), effectsComp->getId(), *iParams);
                    Telegram tel(effectsComp->getId(), effectsComp->getId(), 0.0, msg);
                    core_->getMessageCentre()->addTelegram(tel);
                    ++iParams;
                }
            }
            ++iEffect;

        }

        ++iCom;
    }


}



template <>
void System<EffectsComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to EffectsComps" << std::endl;
    //check if target entity is registered with this subsystem
    EffectsComp* targetComponent = getComponent(message.getTargetId());
    std::cout << "Source component: " << message.getSourceId() << std::endl;
    std::cout << "Target component: " << message.getTargetId() << std::endl;
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];

    if (mainCmd=="add") //e.g. add SpeedBoost
    {
        std::cout << "Message params: " << params.size() << std::endl;
        //check if an effect of this type already exists and if so, end that one before applying this one
        std::string effectName = params[2];
        std::string effectString = params[3];
        if (targetComponent->hasEffect(effectName))
        {
            //carry out onEnd messages
            std::vector<Parameters> endParams = targetComponent->getEffect(effectName)->getOnEnd();
            std::vector<Parameters>::iterator iParams = endParams.begin();
            while(iParams!= endParams.end())
            {
                Message msg(message.getSourceId(), targetComponent->getId(), *iParams);
                Telegram tel(message.getSourceId(), targetComponent->getId(), 0.0, msg);
                core_->getMessageCentre()->addTelegram(tel);
                ++iParams;
            }
        }
        //replace effect
        targetComponent->addEffect(effectName, effectString);

        //carry out onBegin messages
        std::vector<Parameters> beginParams = targetComponent->getEffect(effectName)->getOnBegin();
        std::vector<Parameters>::iterator iParams = beginParams.begin();
        while(iParams!= beginParams.end())
        {
            Message msg(message.getSourceId(), targetComponent->getId(), *iParams);
            Telegram tel(message.getSourceId(), targetComponent->getId(), 0.0, msg);
            core_->getMessageCentre()->addTelegram(tel);
            ++iParams;
        }
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
void System<EffectsComp>::init()
{

}
