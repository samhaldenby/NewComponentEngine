#include "Systems.h"
#include "NameComp.h"
#include <iostream>



template <>
void System<NameComp>::update(double elapsed)
{
//    std::cout << "Updating NameComps" << std::endl;
}


template <>
void System<NameComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to NameComps" << std::endl;
    //check if target entity is registered with this subsystem
    NameComp* targetComponent = getComponent(message.getSourceId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];

    if(mainCmd=="change")
    {
        targetComponent->setName(params[2]);
    }
}



