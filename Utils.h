#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <vector>
#include <string>

typedef std::vector<std::string> StrTokens;

StrTokens tokenise(std::string str, char delimiter);

#endif // UTILS_H_INCLUDED
