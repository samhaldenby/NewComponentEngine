#include "ObjectStore.h"
#include "Object.h"
#include "Core.h"
//#include "GfxSub.h"
//#include "CoordsSub.h"
#include <iostream>


ObjectStore::ObjectStore(Core* core) : core_(core)
{
    idTracker_ = 0;
}



ObjectId ObjectStore::addObject()   //returns id of created object
{
    //create object with id
    objects_.insert(std::pair<ObjectId,Object>(idTracker_ , Object(idTracker_)));
    return idTracker_++;
}

//@@@Requires updating on addition on new subsystem" when adding new subsystems
void ObjectStore::removeObject(ObjectId id)
{

    std::cout << "IMPLEMENT ObjectStore::removeObject(ObjectId id)" << std::endl;
    std::cout << "Deleting object " << id << std::endl;

    std::map<ObjectId,Object>::iterator iObj = objects_.find(id);

    if(iObj==objects_.end())
    {
        std::cout << "This object already destroyed/never existed!" << std::endl;
        return;
    }

    Object* object = &iObj->second;

    //check which components this object has and destroy them
    for(ComponentFlag x=1; x<cFlag::MAX ; x*=2)
    {
        if(object->hasFlag(x))
        {
            std::cout << "Deleting module with flag " << x << std::endl;
            //@ExpandComponent
            switch (x)
            {
                case (cFlag::Gfx):
                {
                    core_->getGfxSub()->removeComponent(id);
                    break;
                }
                case (cFlag::Coords):
                {
                    core_->getCoordsSub()->removeComponent(id);
                    break;
                }
                case (cFlag::Audio):
                {
                    core_->getAudioSub()->removeComponent(id);
                    break;
                }
                case (cFlag::Ai):
                {
                    core_->getAiSub()->removeComponent(id);
                    break;
                }
                case (cFlag::Anchor):
                {
                    core_->getAnchorSub()->removeComponent(id);
                    break;
                }
                case (cFlag::Event):
                {
                    core_->getEventSub()->removeComponent(id);
                    break;
                }
                case (cFlag::Name):
                {
                    core_->getNameSub()->removeComponent(id);
                    break;
                }
                case (cFlag::Move):
                {
                    core_->getMoveSub()->removeComponent(id);
                    break;
                }
//                case (cFlag::Input):
//                {
//                    core_->getInputSub()->removeComponent(id);
//                    break;
//                }
                case (cFlag::Health):
                {
                    core_->getHealthSub()->removeComponent(id);
                    break;
                }
                case (cFlag::Collision):
                {
                    core_->getCollisionSub()->removeComponent(id);
                    break;
                }
//                case (cFlag::OnSelect):
//                {
//                    core_->getOnSelectSub()->removeComponent(id);
//                    break;
//                }
                case (cFlag::Stats):
                {
                    core_->getStatsSub()->removeComponent(id);
                    break;
                }
                case (cFlag::Trigger):
                {
                    core_->getTriggerSub()->removeComponent(id);
                    break;
                }
                default:
                    std::cout << "Cannot find this sub" << std::endl;
            }
        }
    }

    objects_.erase(id);
    std::cout << "Object deleted" << std::endl;
}




Object* ObjectStore::getObject(ObjectId id)
{
    std::map<ObjectId,Object>::iterator iObject = objects_.find(id);
    if(iObject==objects_.end())
    {
        return NULL;
    }

    return &(iObject->second);
}

void ObjectStore::addMessage(Message message)
{
    messages_.push_back(message);
}


void ObjectStore::deliverAllMessages()
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


void ObjectStore::deliverMessage_(Message message)
{
    std::cout << "Delivering message to ObjectStore" << std::endl;
    //check if target entity is registered with this subsystem


    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];

    if (mainCmd=="destroy")
    {
        removeObject(message.getTargetId());
    }
}


