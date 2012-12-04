#include "AnchorComp.h"

AnchorComp::AnchorComp(ObjectId id): Component(id, cType::Anchor)
{
    std::cout << "Creating AnchorComp" << std::endl;
}


void AnchorComp::setParentEntity(ObjectId id)
{
    parentId_ = id;
}


ObjectId AnchorComp::getParentEntity()
{
    return parentId_;
}


void AnchorComp::setOffset(Vector2d v)
{
    offset_ = v;
}


Vector2d AnchorComp::getOffset()
{
    return offset_;
}
