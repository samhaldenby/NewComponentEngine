#ifndef SYSTEMS_H_INCLUDED
#define SYSTEMS_H_INCLUDED


#include "TypeDefs.h"
#include "Message.h"

#include <map>


//forward decs
class Core;


/** Templated base class for all systems
*/
template <class T>
class System
{
    public:
        System(Core* core);

        Core* getCore();

        T* getComponent(ObjectId id);
        void addComponent(ObjectId id);
        void removeComponent(ObjectId id);

        void update(double elapsed);
        void deliverAllMessages();
        void addMessage(Message message);

        void displayStats(ObjectId id);


    private:
        std::vector<Message> messages_;
        Core* core_;
        std::map<ObjectId, T> components_;
        void deliverMessage_(Message message);
};

#endif // SYSTEMS_H_INCLUDED
