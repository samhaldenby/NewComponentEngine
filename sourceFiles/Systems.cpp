#include "Systems.h"
#include "HealthComp.h"
#include "NameComp.h"
#include "CoordsComp.h"
#include "MoveComp.h"
#include "GfxComp.h"
#include "LauncherComp.h"
#include <iostream>
#include <typeinfo>
//@@@Requires updating on addition on new subsystem" when adding new subsystems


template <class T>
System<T>::System(Core* core) : core_(core)
{
    std::cout << "Creating System<" <<  typeid(T).name() << ">" << std::endl;
}


template <class T>
Core* System<T>::getCore()
{
    return core_;
}


template <class T>
T* System<T>::getComponent(ObjectId id)
{
    typename std::multimap<ObjectId, T>::iterator iObj = components_.find(id);
    if(iObj!=components_.end())
    {
        return &(iObj->second);
    }
    else
    {
        return 0;
    }
}


template <class T>
void System<T>::addComponent(ObjectId id)
{
    typename std::multimap<ObjectId, T>::iterator iObj = components_.find(id);
    if(iObj==components_.end())
    {
        components_.insert(typename std::pair<ObjectId, T>(id, T(id)));
        std::cout << "Added component to object " << id << std::endl;
    }
}


template <class T>
void System<T>::removeComponent(ObjectId id)
{
    components_.erase(id);
}


template <class T>
void System<T>::deliverAllMessages()
{
    //read messages
    std::vector<Message>::iterator iMessage = messages_.begin();
    while(iMessage!=messages_.end())
    {
        deliverMessage_(*iMessage);
        ++iMessage;
    }
    //clear messages
    messages_.clear();
}





template<class T>
void System<T>::addMessage(Message message)
{
    messages_.push_back(message);
}






template class System<HealthComp>;
template class System<NameComp>;
template class System<CoordsComp>;
template class System<MoveComp>;
template class System<GfxComp>;
template class System<LauncherComp>;

