#include "Systems.h"
#include "CollisionComp.h"
#include <iostream>
#include "Core.h"
#include "Telegram.h"
#include "Message.h"
#include "MessageCentre.h"
#include "Ui.h"


template <>
void System<CollisionComp>::update(double elapsed)
{
//    std::cout << "Updating CollisionSys" << std::endl;

    //create hash and clear it
    CollisionHash* hash = static_cast<CollisionHash*>(extensions_);
////    static_cast<CollisionHash*>(extensions_);
//    extensions_ = hash;
//    std::cout << "Clearing hash" << std::endl;
    hash->clear();
//    std::cout << "Cleared" << std::endl;

    //update all collision components

    int screenWidth = core_->getUi()->getWindow()->GetWidth();
    int screenHeight = core_->getUi()->getWindow()->GetHeight();
    std::multimap<ObjectId,CollisionComp>::iterator iCom = components_.begin();
    while(iCom!=components_.end())
    {
        CollisionComp* currComponent = &iCom->second;

        //grab coordinates of entity
        CoordsComp* coordsComponent = core_->getCoordsSub()->getComponent(iCom->second.getId());

        //get object id
        ObjectId objId = iCom->second.getId();
        //get position and dimension
        Vector2d topLeft = coordsComponent->getCoords();
        Vector2d dimensions = coordsComponent->getDimensions();
        Vector2d bottomRight = topLeft + dimensions;

        //get rid of entities that go off bottom of screen TODO: Could be implemented as an onOffScreen message?
        if(topLeft.y < -100 || bottomRight.x < -100 || bottomRight.y > screenWidth +100 || topLeft.y > screenHeight + 100)
        {
            Parameters params;
            params.push_back("object");
            params.push_back("destroy");
            Message msg(objId, objId, params);
            Telegram telegram(objId, objId, 0.0, msg);
            core_->getMessageCentre()->addTelegram(telegram);
            ++iCom;
            continue;
        }
        //get hash locations for all four corners
        std::set<GridLocation> locations;
        locations.insert(std::make_pair<int,int>(int(topLeft.x)/MAX_OBJECT_DIMENSION,int(topLeft.y)/MAX_OBJECT_DIMENSION));
        locations.insert(GridLocation(int(topLeft.x)/MAX_OBJECT_DIMENSION,int(bottomRight.y)/MAX_OBJECT_DIMENSION));
        locations.insert(GridLocation(int(bottomRight.x)/MAX_OBJECT_DIMENSION,int(topLeft.y)/MAX_OBJECT_DIMENSION));
        locations.insert(GridLocation(int(bottomRight.x)/MAX_OBJECT_DIMENSION,int(bottomRight.y)/MAX_OBJECT_DIMENSION));
//        std::cout << "SETSIZE: " << locations.size();

        //set hash on component
        currComponent->setSpatialHash(locations);

        //add to hash
        std::set<GridLocation>::iterator iLocs=locations.begin();
        while(iLocs!=locations.end())
        {
            //check if it already exists

            CollisionHash::iterator iFind  = hash->find(*iLocs);

            if(iFind==hash->end())
            {
                std::vector<ObjectId> vec;
                vec.push_back(objId);
//                hash->insert(std::make_pair<GridLocation,std::vector<ObjectId> >(*iLocs,vec));

                hash->insert(std::pair<GridLocation,std::vector<ObjectId> >(*iLocs,vec));
            }
            else
            {
                iFind->second.push_back(objId);
            }
//             hash[*iLocs].push_back(objId);
//            hash->insert(std::make_pair<GridLocation,ObjectId>(*iLocs, objId));
            ++iLocs;
        }

        ++iCom;
    }

    //analyse hash and look for collisions
    std::set<std::pair<ObjectId, ObjectId> > collisions;

    CollisionHash::iterator iHash = hash->begin();
    while(iHash!=hash->end())
    {
        if (iHash->second.size()>1)
        {
            //check all combinations of possible collisions between objects, e.g. A, B, C, D => AB, AC, AD, BC, BD, CD and, by nature, their reverses BA, CA, DA, CB, DB, DC
            for (unsigned int oA = 0; oA < iHash->second.size(); ++oA)
            {
                for (unsigned int oB = oA+1; oB < iHash->second.size(); ++oB) // oB = oA+1 so that it automatically prevents cases of AA checks or BB checks. i.e. if checking oB vs oA, that would be A vs A, whereas oB(oA+1) vs oA would be  B vs A
                {
                    //std::cout << "Checking collision between Objects " << iHash->second[oA] << " and " << iHash->second[oB] << std::endl;
                    //do radial check for collision on coords of objects
                    ObjectId objIdA = iHash->second[oA];
                    ObjectId objIdB = iHash->second[oB];
                    Vector2d coordsA = core_->getCoordsSub()->getComponent(objIdA)->getCoords();
                    Vector2d coordsB = core_->getCoordsSub()->getComponent(objIdB)->getCoords();
                    Vector2d dimsA = core_->getCoordsSub()->getComponent(objIdA)->getDimensions();
                    Vector2d dimsB = core_->getCoordsSub()->getComponent(objIdB)->getDimensions();
                    //mock up a 'radius' TODO: This should be done on creation in coords comp or something!
                    float radiusA = (dimsA.x >= dimsA.y ? float(dimsA.y) /2.0 : float(dimsA.x) / 2.0);
                    float radiusB = (dimsB.x >= dimsB.y ? float(dimsB.y) /2.0 : float(dimsB.x) / 2.0);
                    //calculate max distance between objects to obtain a collision
                    float distForCollision = radiusA + radiusB;
//                    float distAB = sqrt(pow((coordsA.x - coordsB.x),2) + pow((coordsA.y - coordsB.y),2));
                    float distAB = sqrt(pow((coordsA.x + float(dimsA.x) /2.0) - (coordsB.x + float(dimsB.x)/2.0),2) +
                                        pow((coordsA.y + float(dimsA.y) /2.0) - (coordsB.y + float(dimsB.y)/2.0),2));
                    //now, check for collision
                    if (distAB <= distForCollision)
                    {
                        //std::cout << "Collision! " << iHash->second[oA] << " and " << iHash->second[oB] << std::endl;
                        //add collision
                        collisions.insert(std::pair<ObjectId,ObjectId>(iHash->second[oA], iHash->second[oB]));
                        //TODO: Ensure that multiple collisions between same objects does not occur due to entites being present in multiple grid squares, thus being assessed multiple times.
                    }

                }
            }
        }
        ++iHash;
    }

    //Send collision messages
    std::set<std::pair<ObjectId,ObjectId> >::iterator iCol = collisions.begin();
    while(iCol!=collisions.end())
    {
        //grab messages for object A and B
        std::vector<Parameters> aMessages = getComponent(iCol->first)->getOnCollisionMessages();
        std::vector<Parameters> bMessages = getComponent(iCol->second)->getOnCollisionMessages();
        //send a message for each onCollisionMessage that the collision components have
        //aObject messages
        std::vector<Parameters>::iterator iMessage;
        iMessage = aMessages.begin();
        while(iMessage!= aMessages.end())
        {
            //calculate target
            ObjectId targetObject;
            if((*iMessage)[0]=="self")
            {
                targetObject = iCol->first;
            }
            else if ((*iMessage)[0]=="target")
            {
                targetObject = iCol->second;
            }
            else
            {
                std::cout << "ERROR: Incorrect parameter for onCollisionMessage in object (i.e. not 'self' or 'target': " << ((*iMessage)[0]) << std::endl;
                exit(EXIT_FAILURE);
            }


            //grab all params except first one from onCollisionMessage (first one is whether target is self or other)
            Parameters params(iMessage->begin()+1, iMessage->end());
            //build message and dispatch
            Message msg(iCol->first, targetObject, params);
            Telegram telegram(iCol->first, targetObject, 0.0, msg);
            core_->getMessageCentre()->addTelegram(telegram);

            ++iMessage;
        }

        //bObject messages
        iMessage = bMessages.begin();
        while(iMessage!= bMessages.end())
        {
            //calculate target
            ObjectId targetObject;
            if((*iMessage)[0]=="self")
            {
                targetObject = iCol->second;    //not iCol->first, as we're now dealing with how B deals with A, not A deals with B.
            }
            else if ((*iMessage)[0]=="target")
            {
                targetObject = iCol->first;
            }
            else
            {
                std::cout << "ERROR: Incorrect parameter for onCollisionMessage in object (i.e. not 'self' or 'target': " << ((*iMessage)[0]) << std::endl;
                exit(EXIT_FAILURE);
            }

             //grab all params except first one from onCollisionMessage (first one is whether target is self or other)
            Parameters params(iMessage->begin()+1, iMessage->end());
            //build message and dispatch
            Message msg(iCol->second, targetObject, params);
            Telegram telegram(iCol->second, targetObject, 0.0, msg);
            core_->getMessageCentre()->addTelegram(telegram);
            ++iMessage;
        }

        ++iCol;
    }
}


template <>
void System<CollisionComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to LauncherComps" << std::endl;
    //check if target entity is registered with this subsystem
    CollisionComp* targetComponent = getComponent(message.getTargetId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];

//    if (mainCmd=="setMaxCooldown")
//    {
//        targetComponent->setMaxCooldown(atof(params[2].c_str()));
//    }



}


template <>
void System<CollisionComp>::init()
{
    CollisionHash* hash = new CollisionHash;
    extensions_ = hash;
}
