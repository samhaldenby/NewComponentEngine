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

void CoordsComp::setDimensions(Vector2d d)
{
    dimensions_ = d;
}

Vector2d CoordsComp::getDimensions()
{
    return dimensions_;
}

//TODO: really, pretty much all of these should return a reference where ever applicable.
Vector2d CoordsComp::getCenter()
{
//    std::cout << ">>CENTER: " << position_ << " + " << dimensions_ << " /2 = " << position_ + (dimensions_/2) << std::endl;
    return position_ + (dimensions_/2);

}
