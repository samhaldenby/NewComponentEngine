#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <vector>
#include <string>
#include "Vector2d.h"

typedef std::vector<std::string> StrTokens;

StrTokens tokenise(std::string str, char delimiter);


float randf();


#endif // UTILS_H_INCLUDED
