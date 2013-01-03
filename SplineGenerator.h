#ifndef SPLINEGENERATOR_H_INCLUDED
#define SPLINEGENERATOR_H_INCLUDED

#include "TypeDefs.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class SplineGenerator
{
    public:
        static Path makeBezier(int points, int nodes, int seed);
        static Path makeCatmul(int points, int nodes, int seed);
        static void drawSpline(Path p, int x, int y);

    private:
        static Vector2d calculateBezierPoint(float t, Vector2d p0, Vector2d p1, Vector2d p2, Vector2d p3);
        static Vector2d calculateCatmullPoint(float t, Vector2d p0, Vector2d p1, Vector2d p2, Vector2d p3);

};




#endif // SPLINEGENERATOR_H_INCLUDED
