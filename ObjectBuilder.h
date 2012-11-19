#ifndef OBJECTBUILDER_H_INCLUDED
#define OBJECTBUILDER_H_INCLUDED

#include <string>

#include "TypeDefs.h"

//forward declarations
//@@@Update this when adding new component
class Core;
class Object;

class ObjectBuilder
{
    public:
        ObjectBuilder(Core* core);
        ObjectId createObject(std::string blueprintName, NamedParams additionalVars=NamedParams());

    private:
        Core* core_;
        ObjectId idTracker;
        bool addGfxComp_(ObjectId objectId, Object* object, Blueprint* blueprint);
        bool addAudioComp_(ObjectId objectId, Object* object, Blueprint* blueprint);
        bool addAiComp_(ObjectId objectId, Object* object, Blueprint* blueprint);
        bool addEventComp_(ObjectId objectId, Object* object, Blueprint* blueprint);
        bool addNameComp_(ObjectId objectId, Object* object, Blueprint* blueprint);
        bool addCoordsComp_(ObjectId objectId, Object* object, Blueprint* blueprint);
        bool addHealthComp_(ObjectId objectId, Object* object, Blueprint* blueprint);
        bool addMoveComp_(ObjectId objectId, Object* object, Blueprint* blueprint);
        bool addLauncherComp_(ObjectId objectId, Object* object, Blueprint* blueprint);
        bool addCollisionComp_(ObjectId objectId, Object* object, Blueprint* blueprint);



};

#endif // OBJECTBUILDER_H_INCLUDED
