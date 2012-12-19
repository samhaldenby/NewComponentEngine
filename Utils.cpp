#include "Utils.h"
#include <sstream>
#include <iostream>


StrTokens tokenise(std::string str, char delimiter)
{
    StrTokens tokens;
    std::stringstream ss(str);
    std::string token;
    while(getline(ss, token, delimiter))
    {
        tokens.push_back(token);
        std::cout << token << std::endl;
    }

    return tokens;
}

Vector2d calculateBezierPoint(float t,
                              Vector2d p0,
                              Vector2d p1,
                              Vector2d p2,
                              Vector2d p3)
{
    float u   = 1 - t;
    float tt  = t * t;
    float uu  = u * u;
    float uuu = u * u * u;
    float ttt = t * t * t;

    Vector2d p = p0 * uuu; //first term
    p += p1 * (uu * 3  * t); //second term
    p += p2 * (3 * u * tt) ; //third term
    p += p3 * ttt; //fourth term

    return p;
}

////////////
//p1 and p2 define section
//t is proprtion across p1-p2
//p3 and p0 bend the curve, I guess!
Vector2d calculateCatmullPoint(float t,
                               Vector2d p0,
                               Vector2d p1,
                               Vector2d p2,
                               Vector2d p3)
{
    float tt  = t * t;
    float ttt = tt * t;
    Vector2d p;
    p.x = 0.5f * ((p1.x * 2.0f) + (p2.x - p0.x) * t +
    (p0.x * 2.0f - p1.x * 5.0f + p2.x * 4.0f - p3.x) * tt +
    (p0.x * -1.0f + p1.x * 3.0f + p2.x * -3.0f + p3.x) * ttt);

    p.y = 0.5f * ((p1.y * 2.0f) + (p2.y - p0.y) * t +
    (p0.y * 2.0f - p1.y * 5.0f + p2.y * 4.0f - p3.y) * tt +
    (p0.y * -1.0f + p1.y * 3.0f + p2.y * -3.0f + p3.y) * ttt);

    return p;
}
