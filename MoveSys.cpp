#include "Systems.h"
#include "MoveComp.h"
#include "CoordsComp.h"
#include "Core.h"
#include <iostream>

template <>
void System<MoveComp>::update(double elapsed)
{
    std::cout << "Updating MoveComps" << std::endl;

    //update all health components
    std::map<ObjectId,MoveComp>::iterator iCom = components_.begin();
    while(iCom!=components_.end())
    {
        MoveComp* currComp = &iCom->second;
        //grab corresponding Coords comp
        CoordsComp* coordsComp = core_->getCoordsSub()->getComponent(iCom->second.getId());

        //check dist from target
        double distFromTarget = sqrt(pow(coordsComp->getCoords().x -currComp->getLocalDestination().x , 2) *
                                pow(coordsComp->getCoords().y -currComp->getLocalDestination().y , 2));


        if (distFromTarget <= MIN_DIST)
        {
            currComp->setMove(Vector2d(0,0));
        }
        else
        {
            //determine move speeds
            double distX = currComp->getLocalDestination().x - coordsComp->getCoords().x;
            double distY = currComp->getLocalDestination().y - coordsComp->getCoords().y;

            currComp->setMove(Vector2d(distX/distFromTarget, distY/distFromTarget));
        }

        //now move
        coordsComp->setCoords(coordsComp->getCoords() + currComp->getMove());

        ++iCom;
    }


}


template <>
void System<MoveComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to MoveComps" << std::endl;
    //check if target entity is registered with this subsystem
    MoveComp* targetComponent = getComponent(message.getSourceId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];

    if (mainCmd=="setLocalDest")
    {
        targetComponent->setLocalDestination(Vector2d(atoi(params[2].c_str()),atoi(params[3].c_str())));
    }
//
//    else if (mainCmd=="changeCurrBy")
//    {
//        targetComponent->setCurrent(targetComponent->getCurrent() + atoi(params[2].c_str()));
//    }


}
