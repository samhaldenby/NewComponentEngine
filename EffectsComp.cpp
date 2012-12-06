#include "EffectsComp.h"

//TODO: Massive memory leaks in EffectsComp!!!
EffectsComp::EffectsComp(ObjectId id) : Component(id, cType::Effects)
{
    std::cout << "Creating EffectsComp" << std::endl;
    testString ="This is working at least";
}


void EffectsComp::addEffect(std::string effectName, std::string effectString)
{
    std::cout << "Adding " <<effectName << " as " << effectString << std::endl;
    //will overwrite pre-existing effect
//    effectsMap_[effectName]=e;

    effectsMap_[effectName]=new Effect(effectString);
//    effectsMap_.insert(std::pair<std::string,Effect*>(effectName,new Effect(effectString)));
}



bool EffectsComp::hasEffect(std::string effectName)
{
    EffectsMap::iterator iFind = effectsMap_.find(effectName);
    if (iFind==effectsMap_.end())
    {
        return false;
    }

    return true;
}


Effect* EffectsComp::getEffect(std::string effectName)
{
    EffectsMap::iterator iFind = effectsMap_.find(effectName);
    if (iFind==effectsMap_.end())
    {
        return NULL;
    }
    else
    {
        return iFind->second;
    }
}


void EffectsComp::removeEffect(std::string effectName)
{
    EffectsMap::iterator iFind = effectsMap_.find(effectName);
    if (iFind!=effectsMap_.end())
    {
        effectsMap_.erase(iFind);
    }

}


void EffectsComp::clearEffects()
{
    effectsMap_.clear();
}



EffectsMap* EffectsComp::getEffects()
{
    return &effectsMap_;
}



