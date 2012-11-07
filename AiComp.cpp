#include "AiComp.h"
#include "Store.h"


AiComp::AiComp(ObjectId id) : Component(id, cType::Ai)
{
    std::cout << "Creating AiComp" << std::endl;
}
