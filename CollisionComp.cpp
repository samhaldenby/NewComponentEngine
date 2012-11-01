#include "CollisionComp.h"


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
