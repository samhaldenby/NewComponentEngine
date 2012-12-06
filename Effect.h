#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED

#include "TypeDefs.h"
//////
// Has an effect on an object

class Effect
{
    public:

        Effect(std::string effectString);
        void setActive(bool a);
        bool isActive();
        void setOnBegin(std::string);
        void setOnUpdate(std::string);
        void setOnEnd(std::string);
        void setDuration(double duration);
        void updateDuration(double elapsed);
        bool hasDuration();
        bool hasExpired();
        std::vector<Parameters> getOnBegin();
        std::vector<Parameters> getOnUpdate();
        std::vector<Parameters> getOnEnd();


    private:
        std::vector<Parameters> onBeginParams_;
        std::vector<Parameters> onUpdateParams_;
        std::vector<Parameters> onEndParams_;
        bool active_;
        bool hasDuration_;

        double duration_;
};





#endif // EFFECT_H_INCLUDED
