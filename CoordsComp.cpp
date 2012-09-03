#include "CoordsComp.h"

CoordsComp::CoordsComp(ObjectId id): Component(id, cType::Coords)
{
    std::cout << "Creating CoordsComp" << std::endl;
}


void CoordsComp::setCoords(Vector2d v)
{
    position_ = v;
}

Vector2d CoordsComp::getCoords()
{
    return position_;
}
