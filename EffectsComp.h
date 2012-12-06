#ifndef EFFECTSCOMP_H_INCLUDED
#define EFFECTSCOMP_H_INCLUDED

#include "Components.h"
#include "TypeDefs.h"
#include "Effect.h"



//TODO: So much of this needs passing by pointer, not by value!

class EffectsComp : public Component
{
    public:
        EffectsComp(ObjectId id);
        void addEffect(std::string effectName, std::string effectString);
        bool hasEffect(std::string effectName);
        Effect* getEffect(std::string effectName);
        void removeEffect(std::string effectName);
        void clearEffects();
        EffectsMap* getEffects();
    private:
        EffectsMap effectsMap_;
        std::string testString;
};







#endif // EFFECTSCOMP_H_INCLUDED
