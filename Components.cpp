#include "Components.h"

Component::Component(ObjectId id, CompType compType)
{
    id_ = id;
    type_=compType;
}

Component::~Component()
{
    std::cout << "Deleting component" << std::endl;
}

ObjectId Component::getId()
{
    return id_;
}

CompType Component::getType()
{
    return type_;
}
