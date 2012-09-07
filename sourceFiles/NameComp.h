#ifndef NAMECOMP_H_INCLUDED
#define NAMECOMP_H_INCLUDED

#include "Components.h"
#include <string>

class NameComp : public Component
{
    private:
        std::string name_;
    public:
        NameComp(ObjectId id);
        void setName(std::string name);
        std::string getName();
};

#endif // NAMECOMP_H_INCLUDED
