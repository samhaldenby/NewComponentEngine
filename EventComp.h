#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include "Components.h"
#include "TypeDefs.h"

class EventComp : public Component
{
    public:
        EventComp(ObjectId id);
        void addEvents(std::string key, std::string eventMessage);
        void removeEvent(std::string key);
        std::vector<Parameters>* getEvents(std::string key);

    private:
        std::map<std::string, std::vector<Parameters> > eventMap_;

};

#endif // EVENT_H_INCLUDED
