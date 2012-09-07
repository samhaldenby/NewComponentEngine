#include "CollisionComp.h"


CollisionComp::CollisionComp(ObjectId id): Component(id, cType::Collision)
{
    std::cout << "Creating CollisionComp" << std::endl;
}


void CollisionComp::setSpatialHash(int hash)
{
    spatialHash_ = hash;
}


int CollisionComp::getSpatialHash()
{
    return spatialHash_;
}
