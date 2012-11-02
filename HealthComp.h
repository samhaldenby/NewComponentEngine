#ifndef HEALTHCOMP_H_INCLUDED
#define HEALTHCOMP_H_INCLUDED

#include "Components.h"

class HealthComp : public Component
{
    private:
        int max_;
        int current_;
        std::vector<Parameters> onZeroHealthMessages_;
    public:

        HealthComp(ObjectId id);

        void setMax(int max);

        void setCurrent(int current);

        int getMax();

        int getCurrent();

        void addOnZeroHealthMessages(std::string str);

        std::vector<Parameters> getOnZeroHealthMessages();

};


#endif // HEALTHCOMP_H_INCLUDED
