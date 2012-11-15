#ifndef COMPONENTS_H_INCLUDED
#define COMPONENTS_H_INCLUDED

#include "TypeDefs.h"

/** Base class for all components
*/
class Component
{
    private:
        ObjectId id_;
        CompType type_;
    public:
        Component(ObjectId id, CompType compType);
        ObjectId getId();
        CompType getType();
        virtual ~Component();
};

#endif // COMPONENTS_H_INCLUDED
