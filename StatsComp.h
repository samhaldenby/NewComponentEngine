#ifndef STATSCOMP_H_INCLUDED
#define STATSCOMP_H_INCLUDED

#include "Components.h"
#include "TypeDefs.h"

class StatsComp : public Component
{
    public:
        StatsComp(ObjectId id);
        void addStat(std::string statName, double value);
        void removeStat(std::string statName);
        void modifyStat(std::string statName, double modValue);
        void setStat(std::string statName, double value);
        double getStat(std::string statName, double defaultValue);
        bool hasStat(std::string statName);
    private:
        StatsMap stats_;
};


#endif // FACTIONCOMP_H_INCLUDED
