#ifndef HEALTHCOMP_H_INCLUDED
#define HEALTHCOMP_H_INCLUDED

#include "Components.h"

class HealthComp : public Component
{
    private:
        int max_;
        int current_;
    public:

        HealthComp(ObjectId id);

        void setMax(int max);

        void setCurrent(int current);

        int getMax();

        int getCurrent();

};


#endif // HEALTHCOMP_H_INCLUDED
