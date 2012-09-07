#ifndef COLLISIONCOMP_H_INCLUDED
#define COLLISIONCOMP_H_INCLUDED

#include "Components.h"
#include "TypeDefs.h"

class CollisionComp : public Component
{
    public:
        CollisionComp(ObjectId id);
        void setSpatialHash(int hash);
        int getSpatialHash();
    private:
        int spatialHash_;

};

#endif // COLLISIONCOMP_H_INCLUDED
