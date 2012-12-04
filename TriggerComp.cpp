#include "TriggerComp.h"

TriggerComp::TriggerComp(ObjectId id): Component(id, cType::Trigger)
{
    std::cout << "Creating TriggerComp" << std::endl;
}


void TriggerComp::addReceiverObject(std::string tag, ObjectId id)
{
    //see if tag already present in map
    std::map<std::string, std::vector<ObjectId> >::iterator iFind = tagObjectMap_.find(tag);
    if(iFind==tagObjectMap_.end())
    {
        //add to map
        tagObjectMap_[tag]=std::vector<ObjectId>();
    }

    tagObjectMap_[tag].push_back(id);
}


std::vector<ObjectId> TriggerComp::getTriggeredObjects(std::string tag)
{
    //see if tag present in map
    std::map<std::string, std::vector<ObjectId> >::iterator iFind = tagObjectMap_.find(tag);
    if(iFind!=tagObjectMap_.end())
    {
        return tagObjectMap_[tag];
    }
    else
    {
        return std::vector<ObjectId>();
    }
}


void TriggerComp::addMessageParams(std::string tag, Parameters params)
{
    //see if tag already present in map
    std::map<std::string, std::vector<Parameters> >::iterator iFind = tagParamsMap_.find(tag);
    if(iFind==tagParamsMap_.end())
    {
        //add to map
        tagParamsMap_[tag]=std::vector<Parameters>();
    }
    std::cout << "Adding params:" << std::endl;
    for (int x=0; x< params.size(); ++x)
    {
        std::cout << "\t" << x+1 << ": " << params[x] << std::endl;
    }
    std::cout << " added to tag " << tag << std::endl;

    tagParamsMap_[tag].push_back(params);
}


std::vector<Parameters> TriggerComp::getTriggeredParameters(std::string tag)
{
     //see if tag present in map
    std::map<std::string, std::vector<Parameters> >::iterator iFind = tagParamsMap_.find(tag);
    if(iFind!=tagParamsMap_.end())
    {
        return tagParamsMap_[tag];
    }
    else
    {
        return std::vector<Parameters>();
    }
}


