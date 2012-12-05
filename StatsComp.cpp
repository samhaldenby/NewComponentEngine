#include "StatsComp.h"

StatsComp::StatsComp(ObjectId id): Component(id, cType::Stats)
{
    std::cout << "Creating StatsComp" << std::endl;
}

void StatsComp::addStat(std::string statName, double value = 0)
{
    //see if already exists
    StatsMap::iterator iStat = stats_.find(statName);
    if(iStat==stats_.end())
    {
        //add stat and set
        std::cout << "Creating stat '" << statName << "' and setting to " << value << " in object " << getId() << std::endl;
        stats_.insert(std::pair<std::string,double>(statName, value));
    }
    else
    {
        std::cout << "Stat '" << statName << "' already exists in object " << getId() << std::endl;
    }
}


void StatsComp::removeStat(std::string statName)
{
    //see if it exists
    StatsMap::iterator iStat = stats_.find(statName);
    if(iStat==stats_.end())
    {
        std::cout << "Stat '" << statName << "' not present in object " << getId() << std::endl;
    }
    else
    {
        //remove stat
        std::cout << "Removing stat '" << statName << "' from object " << getId() << std::endl;
        stats_.erase(iStat);
    }
}


void StatsComp::modifyStat(std::string statName, double modValue)
{
    //see if it exists
    StatsMap::iterator iStat = stats_.find(statName);
    if(iStat==stats_.end())
    {
        std::cout << "Stat '" << statName << "' not present in object " << getId() << " therefore not changing anything" << std::endl;
    }
    else
    {
        //modify stats
        std::cout << "Object " << getId() << " : Stat : " << statName << " : " << iStat->second;
        iStat->second = iStat->second + modValue;
        std::cout << " -> " << iStat->second << std::endl;
    }
}


void StatsComp::setStat(std::string statName, double value)
{
    //see if it exists
    StatsMap::iterator iStat = stats_.find(statName);
    if(iStat==stats_.end())
    {
        std::cout << "Stat '" << statName << "' not present in object " << getId() << " therefore not changing anything" << std::endl;
    }
    else
    {
        //modify stats
        std::cout << "Object " << getId() << " : Stat : " << statName << " : " << iStat->second;
        iStat->second = value;
        std::cout << " -> " << iStat->second << std::endl;
    }
}


double StatsComp::getStat(std::string statName, double defaultValue=-1)
{
    //see if it exists
    StatsMap::iterator iStat = stats_.find(statName);
    if(iStat==stats_.end())
    {
        return defaultValue;
    }
    else
    {
       return iStat->second;
    }
}


bool StatsComp::hasStat(std::string statName)
{
    //see if it exists
    StatsMap::iterator iStat = stats_.find(statName);
    if(iStat==stats_.end())
    {
        return false;
    }
    else
    {
       return true;
    }
}
