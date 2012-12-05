#include "Systems.h"
#include "StatsComp.h"
#include <iostream>

template <>
void System<StatsComp>::update(double elapsed)
{
//    std::cout << "Updating CoordsComp" << std::endl;

    //update all coords components
    std::multimap<ObjectId,StatsComp>::iterator iCom = components_.begin();
    while(iCom!=components_.end())
    {
        StatsComp* currComponent = &iCom->second;

        ++iCom;
    }


}


template <>
void System<StatsComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to StatsComps" << std::endl;
    //check if target entity is registered with this subsystem
    StatsComp* targetComponent = getComponent(message.getTargetId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];
    std::string statsName = params[2];
    double value = 0.0;
    if (params.size()>3)
    {
        value = atof(params[3].c_str());
    }

    if (mainCmd=="add")
    {
        targetComponent->addStat(statsName, value);
    }

    else if (mainCmd=="set")
    {
        targetComponent->setStat(statsName, value);
    }

    else if (mainCmd=="modify")
    {
        targetComponent->modifyStat(statsName, value);
    }

    else if (mainCmd=="remove")
    {
        targetComponent->removeStat(statsName);
    }
}



template <>
void System<StatsComp>::init()
{

}
