#include "Systems.h"
#include "CollisionComp.h"
#include <iostream>
#include "Core.h"
#include "Telegram.h"
#include "Message.h"
#include "MessageCentre.h"

//template <>
//inline System<CollisionComp>::System(Core* core) : core_(core)
//{
//    std::cout << "Creating System<CollisionComp>" << std::endl;
//
//    extensions_ = new CollisionHash*;
//}


template <>
void System<CollisionComp>::update(double elapsed)
{
//    std::cout << "Updating CollisionSys" << std::endl;

    //create hash and clear it
    CollisionHash* hash = new CollisionHash;
//    static_cast<CollisionHash*>(extensions_);
    extensions_ = hash;
//    std::cout << "Clearing hash" << std::endl;
    hash->clear();
//    std::cout << "Cleared" << std::endl;

    //update all collision components
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

    //debug: print out grid
    CollisionHash::iterator iHash = hash->begin();
    while(iHash!=hash->end())
    {
        if (iHash->second.size()>1)
        {
            std::cout << "POTENTIAL COLLISSION: " << iHash->first.first << "," << iHash->first.second << std::endl;
            for (int x=0; x< iHash->second.size(); ++x)
            {
                std::cout << iHash->second[x] << ",";
                std::cout << core_->getCoordsSub()->getComponent(iHash->second[x])->getCoords() << std::endl;
            }
//            std::cout << std::endl;
        }
//        std::cout << (*iHash).first.first << "," << (*iHash).first.second << "\t" << iHash->second.size() << std::endl;// << (*iHash).second << std::endl;
        ++iHash;
    }
}


template <>
void System<CollisionComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to LauncherComps" << std::endl;
    //check if target entity is registered with this subsystem
    CollisionComp* targetComponent = getComponent(message.getSourceId());
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
