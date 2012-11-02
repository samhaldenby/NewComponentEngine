#ifndef OBJECTSTORE_H_INCLUDED
#define OBJECTSTORE_H_INCLUDED

#include <map>
#include "TypeDefs.h"
#include "Message.h"
//forward declarations
class Core;
class Object;

class ObjectStore
{
    public:
        ObjectStore(Core* core);
        ObjectId addObject();   //returns id of created object
        void removeObject(ObjectId);
        Object* getObject(ObjectId);
        void addMessage(Message message);
        void deliverAllMessages();
        void displayStats(ObjectId id);





    private:
        std::vector<Message> messages_;
        Core* core_;
        ObjectId idTracker_;
        std::map<ObjectId, Object> objects_;

        void deliverMessage_(Message message);
};


#endif // OBJECTSTORE_H_INCLUDED
