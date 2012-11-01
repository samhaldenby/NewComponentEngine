#include "Systems.h"
#include "MoveComp.h"
#include "CoordsComp.h"
#include "Core.h"
#include <iostream>

template <>
void System<MoveComp>::update(double elapsed)
{
//    std::cout << "Updating MoveComps" << std::endl;

    //update all health components
    std::multimap<ObjectId,MoveComp>::iterator iCom = components_.begin();
    while(iCom!=components_.end())
    {
        MoveComp* currComp = &iCom->second;
        //grab corresponding Coords comp
        CoordsComp* coordsComp = core_->getCoordsSub()->getComponent(iCom->second.getId());

        //check dist from target
        double distFromTarget = sqrt(pow(coordsComp->getCoords().x -currComp->getLocalDestination().x , 2) +
                                pow(coordsComp->getCoords().y -currComp->getLocalDestination().y , 2));



        if (currComp->getLocalDestination().x==-1) //i.e. no dest MAGIC NUMBER
        {

        }
        else if (distFromTarget <= MIN_DIST)
        {
            currComp->setMove(Vector2d(0,0));
            currComp->setLocalDestination(Vector2d(-1,-1)); //MAGIC NUMBER
        }
        else
        {
            //determine move speeds
            //std::cout << "Determining move speed of Entity" << iCom->first << std::endl;
            double distX = currComp->getLocalDestination().x - coordsComp->getCoords().x;
            double distY = currComp->getLocalDestination().y - coordsComp->getCoords().y;
            //std::cout << distX << "\t" << distY << "\t" << distFromTarget << std::endl;

            currComp->setMove(Vector2d(distX/distFromTarget, distY/distFromTarget));
            //std::cout << currComp->getMove() << "\t(" << coordsComp->getCoords() << ")" << std::endl;
        }

        //now move
        coordsComp->setCoords(coordsComp->getCoords() + currComp->getMove());
//        std::cout << "Moving obj " << iCom->first << " (" << coordsComp->getCoords() << ")" << std::endl;

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
    else if (mainCmd=="setVelocity")
    {
        targetComponent->setMove(Vector2d(atof(params[2].c_str()),atof(params[3].c_str())));
    }
//
//    else if (mainCmd=="changeCurrBy")
//    {
//        targetComponent->setCurrent(targetComponent->getCurrent() + atoi(params[2].c_str()));
//    }


}
