#include "EventComp.h"
#include "Utils.h"
#include "Store.h"


EventComp::EventComp(ObjectId id) : Component(id, cType::Audio)
{
    std::cout << "Creating EventComp" << std::endl;
}



void EventComp::addEvents(std::string key, std::string eventMsg)
{
    std::cout << "Adding " << key << "event message : "  << eventMsg << " : to object " << this->getId() << std::endl;
    //Parametise by ;
    Parameters msgStr = tokenise(eventMsg,';');
    std::vector<Parameters> msgs;
    for (int x=0; x< msgStr.size(); ++x)
    {
        Parameters params = tokenise(msgStr[x],' ');
        msgs.push_back(params);
        std::cout << ">> " << key << " : " << msgStr[x] << std::endl;
        int dump; std::cin >> dump;
    }


    eventMap_.insert(std::pair<std::string,std::vector<Parameters> >(key,msgs));
}



void EventComp::removeEvent(std::string key)
{
    std::cout << "Removing event [" << key << "] from object " << this->getId() << std::endl;

    //search for key
    std::map<std::string, std::vector<Parameters> >::iterator iParams = eventMap_.find(key);
    if(iParams==eventMap_.end())
    {
        std::cout << "Warning : This event does not exist or was already deleted" << std::endl;
        return;
    }

    eventMap_.erase(iParams);

}



std::vector<Parameters>* EventComp::getEvents(std::string key)
{
    std::map<std::string, std::vector<Parameters> >::iterator iParams = eventMap_.find(key);
    if(iParams==eventMap_.end())
    {
        std::cout << "Warning : This event does not exist or was already deleted" << std::endl;
        return NULL;
    }
    else
    {
        return &iParams->second;
    }
}
