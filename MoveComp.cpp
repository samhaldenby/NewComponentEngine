#include "MoveComp.h"

void setMove(Vector2d v);
Vector2d getMove();

MoveComp::MoveComp(ObjectId id): Component(id, cType::Move)
{
    std::cout << "Creating MoveComp" << std::endl;
}


void MoveComp::setMove(Vector2d v)
{
    move_ = v;
}

Vector2d MoveComp::getMove()
{
    return move_;
}

void MoveComp::setLocalDestination(Vector2d d)
{
    localDestination_ = d;
}

Vector2d MoveComp::getLocalDestination()
{
    return localDestination_;
}
