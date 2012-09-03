#include "NameComp.h"
#include <iostream>

NameComp::NameComp(ObjectId id) : Component(id, cType::Name)
{
    std::cout << "Creating NameComp" << std::endl;
}

void NameComp::setName(std::string name)
{
    name_ = name;
}

std::string NameComp::getName()
{
    return name_;
}
