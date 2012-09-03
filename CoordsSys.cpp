#include "Systems.h"
#include "CoordsComp.h"
#include <iostream>

template <>
void System<CoordsComp>::update(double elapsed)
{
//    std::cout << "Updating CoordsComp" << std::endl;

    //update all coords components
    std::map<ObjectId,CoordsComp>::iterator iCom = components_.begin();
    while(iCom!=components_.end())
    {
        CoordsComp* currComponent = &iCom->second;

        ++iCom;
    }


}


template <>
void System<CoordsComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to CoordsComps" << std::endl;
    //check if target entity is registered with this subsystem
    CoordsComp* targetComponent = getComponent(message.getSourceId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];

    if (mainCmd=="setCoords")
    {
        targetComponent->setCoords(Vector2d(atoi(params[2].c_str()),atoi(params[3].c_str())));
    }
}
