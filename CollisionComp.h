#ifndef COLLISIONCOMP_H_INCLUDED
#define COLLISIONCOMP_H_INCLUDED

#include "Components.h"
#include "TypeDefs.h"
#include <set>

class CollisionComp : public Component
{
    public:
        CollisionComp(ObjectId id);
        void setSpatialHash(std::set<GridLocation> gridLocationSet);
        std::set<GridLocation>* getSpatialHash();
    private:
        std::set<GridLocation> spatialHash_;

};

#endif // COLLISIONCOMP_H_INCLUDED
