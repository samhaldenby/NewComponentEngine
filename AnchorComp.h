#ifndef ANCHORCOMP_H_INCLUDED
#define ANCHORCOMP_H_INCLUDED

#include "Components.h"
#include "TypeDefs.h"
#include "Vector2d.h"

/////
// Allows spatial linking of entities.
// Will maintain position relative to 'parent' entity (accounting for offset)
// Will die when parent dies, but will not kill parent when it dies.
class AnchorComp : public Component
{
    public:
        AnchorComp(ObjectId id);
        void setParentEntity(ObjectId id);
        ObjectId getParentEntity();
        void setOffset(Vector2d v);
        Vector2d getOffset();

    private:
        ObjectId parentId_;
        Vector2d offset_;
};


#endif // ANCHORCOMP_H_INCLUDED
