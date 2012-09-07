#include "HealthComp.h"
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
