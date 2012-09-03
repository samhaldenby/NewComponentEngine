#ifndef MOVECOMP_H_INCLUDED
#define MOVECOMP_H_INCLUDED

#include "Components.h"
#include "Vector2d.h"
#include "TypeDefs.h"

class MoveComp : public Component
{
    public:
        enum MoveStatus
        {
            StoppedAtDest, StoppedNotAtDest, MovingToTarget, MovingNotToTarget
        };
        MoveComp(ObjectId id);
        void setMove(Vector2d v);
        Vector2d getMove();
        void setLocalDestination(Vector2d v);
        Vector2d getLocalDestination();
    private:
        Vector2d move_;
        Vector2d localDestination_;
};


#endif // MOVECOMP_H_INCLUDED
