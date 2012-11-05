#include "AudioComp.h"
#include "Store.h"


AudioComp::AudioComp(ObjectId id) : Component(id, cType::Audio)
{
    std::cout << "Creating AudioComp" << std::endl;
}



void AudioComp::addSound(std::string key, sf::SoundBuffer* soundBuffer)
{
    std::cout << "Adding sound buffer as [" << key << "] to object " << this->getId() << std::endl;
    soundMap_.insert(std::pair<std::string,sf::SoundBuffer*>(key,soundBuffer));
}



void AudioComp::removeSound(std::string key)
{
    std::cout << "Removing sound [" << key << "] from object " << this->getId() << std::endl;

    //search for key
    std::map<std::string, sf::SoundBuffer*>::iterator iSound = soundMap_.find(key);
    if(iSound==soundMap_.end())
    {
        std::cout << "Warning : This sound does not exist of was already deleted" << std::endl;
        return;
    }

    soundMap_.erase(iSound);

}



sf::SoundBuffer* AudioComp::getSound(std::string key)
{
    std::map<std::string, sf::SoundBuffer*>::iterator iSound = soundMap_.find(key);
    if(iSound==soundMap_.end())
    {
        std::cout << "Warning : This sound does not exist of was already deleted" << std::endl;
        return NULL;
    }
    else
    {
        return iSound->second;
    }
}


