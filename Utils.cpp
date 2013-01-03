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

float randf()
{
    return (float)rand()/(float)RAND_MAX;
}


