#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <vector>
#include <string>
#include "Vector2d.h"

typedef std::vector<std::string> StrTokens;

StrTokens tokenise(std::string str, char delimiter);



Vector2d calculateCatmullPoint(float t,
                               Vector2d p0,
                               Vector2d p1,
                               Vector2d p2,
                               Vector2d p3);
#endif // UTILS_H_INCLUDED
