#ifndef TRIGGERCOMP_H_INCLUDED
#define TRIGGERCOMP_H_INCLUDED

#include "Components.h"


/////
// Like AnchorComp, links objects together
// However, this links to children, rather than to parents
// useful for objects which affect other objects activities, e.g. ship controlling gun object
class TriggerComp : public Component
{
    public:
        TriggerComp(ObjectId id);
        void addReceiverObject(std::string tag, ObjectId id);
        std::vector<ObjectId> getTriggeredObjects(std::string tag);
        void addMessageParams(std::string tag, Parameters params);
        std::vector<Parameters> getTriggeredParameters(std::string tag);
        void removeReceiverObject(std::string, ObjectId); //TODO: will remove a single id from  a trigger
        void removeReceiverObject(ObjectId); //TODO: will remove a single id from all triggers
        void cleanUpReceivers(); //TODO: Will scan all receivers, analyse messages and decide which ones are valid (i.e. if 'launch' is in message for 'gun', check all 'gun' objectIds and remove any which don';t have launchers...) must be a better way of doing this!!! Surely should be in the actual system too, not the comp

    private:
        std::map<std::string, std::vector<ObjectId> > tagObjectMap_;
        std::map<std::string, std::vector<Parameters> >tagParamsMap_;
};
;;;

#endif // TRIGGERCOMP_H_INCLUDED
