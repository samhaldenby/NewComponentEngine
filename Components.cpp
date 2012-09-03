#include "Components.h"

Component::Component(ObjectId id, CompType compType)
{
    id_ = id;
    type_=compType;
}

ObjectId Component::getId()
{
    return id_;
}

CompType Component::getType()
{
    return type_;
}
