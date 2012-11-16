#ifndef OBJECTBUILDER_H_INCLUDED
#define OBJECTBUILDER_H_INCLUDED

#include <string>

#include "TypeDefs.h"

//forward declarations
class Core;

class ObjectBuilder
{
    public:
        ObjectBuilder(Core* core);
        ObjectId createObject(std::string blueprintName, NamedParams additionalVars=NamedParams());

    private:
        Core* core_;
        ObjectId idTracker;
};

#endif // OBJECTBUILDER_H_INCLUDED
