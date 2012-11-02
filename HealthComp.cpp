#include "HealthComp.h"
#include "Utils.h"
#include <iostream>

HealthComp::HealthComp(ObjectId id) : Component(id, cType::Health)
{
    std::cout << "Creating HealthComp" << std::endl;
}

void HealthComp::setMax(int max)
{
    max_ = max;
}

void HealthComp::setCurrent(int current)
{
    current_ = current;
}

int HealthComp::getMax()
{
    return max_;
}

int HealthComp::getCurrent()
{
    return current_;
}


void HealthComp::addOnZeroHealthMessages(std::string str)
{
     //break string into messages
    StrTokens messages = tokenise(str,';');
    StrTokens::iterator iMessage = messages.begin();
    //add to message list
    while(iMessage!=messages.end())
    {
        //split message into words
        Parameters params = tokenise(*iMessage,' '); //NB: Parameters === StrTokens
        onZeroHealthMessages_.push_back(params);
        ++iMessage;
    }
}

std::vector<Parameters> HealthComp::getOnZeroHealthMessages()
{

    return onZeroHealthMessages_;
}
