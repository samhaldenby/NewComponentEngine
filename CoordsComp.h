#ifndef COORDSCOMP_H_INCLUDED
#define COORDSCOMP_H_INCLUDED

#include "Components.h"
#include "Vector2d.h"
#include "TypeDefs.h"

class CoordsComp : public Component
{
    public:
        CoordsComp(ObjectId id);
        void setCoords(Vector2d v);
        Vector2d getCoords();
        void setDimensions(Vector2d d);
        Vector2d getDimensions();
        Vector2d getCenter();
    private:
        Vector2d position_;
        Vector2d dimensions_;
};

#endif // COORDSCOMP_H_INCLUDED
