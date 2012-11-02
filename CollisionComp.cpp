#include "CollisionComp.h"
#include "Utils.h"


CollisionComp::CollisionComp(ObjectId id): Component(id, cType::Collision)
{
    std::cout << "Creating CollisionComp" << std::endl;
    spatialHash_ = std::set<GridLocation>();
}


void CollisionComp::setSpatialHash(std::set<GridLocation> gridLocationSet)
{
    spatialHash_ = gridLocationSet;
}


std::set<GridLocation>* CollisionComp::getSpatialHash()
{
    return &spatialHash_;
}

void CollisionComp::addOnCollisionMessages(std::string str)
{
    //break string into messages
    StrTokens messages = tokenise(str,';');
    StrTokens::iterator iMessage = messages.begin();
    //add to message list
    while(iMessage!=messages.end())
    {
        //split message into words
        Parameters params = tokenise(*iMessage,' '); //NB: Parameters === StrTokens
        onCollisionMessages_.push_back(params);
        ++iMessage;
    }


}

std::vector<Parameters> CollisionComp::getOnCollisionMessages()
{
    return onCollisionMessages_;
}
