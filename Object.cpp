#include <iostream>

#include "Object.h"
#include "Core.h"
#include "Message.h"



Core* Object::core_ = NULL;

void Object::setCore(Core* core)
{
    core_ = core;
}



Object::Object(ObjectId id) : id_(id)
{
    std::cout << "Object created with id " << id << std::endl;

    flags_ = 0;
}



void Object::addFlag(ComponentFlag flag)
{
    flags_ = flags_ | flag;
}



bool Object::hasFlag(ComponentFlag flag)
{
    return ((flags_ & flag) > 0);
}




