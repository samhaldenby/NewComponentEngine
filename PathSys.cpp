#include "Systems.h"
#include "PathComp.h"
#include <iostream>

template <>
void System<PathComp>::update(double elapsed)
{
//    std::cout << "Updating CoordsComp" << std::endl;

    //update all coords components
//    std::multimap<ObjectId,PathComp>::iterator iCom = components_.begin();
//    while(iCom!=components_.end())
//    {
//        PathComp* currComponent = &iCom->second;
//
//        ++iCom;
//    }


}


template <>
void System<PathComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to PathComps" << std::endl;
    //check if target entity is registered with this subsystem
    PathComp* targetComponent = getComponent(message.getTargetId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];
    double value = 0.0;

    if (mainCmd=="set")
    {
        //see what path is to be set by number or random
//        if (params[2]=="random")
//        {
//            sthis->extensions_
    }


}



template <>
void System<PathComp>::init()
{

}
