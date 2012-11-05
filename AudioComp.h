#ifndef AUDIOCOMP_H_INCLUDED
#define AUDIOCOMP_H_INCLUDED

#include "Components.h"
#include "TypeDefs.h"
#include <SFML/Audio.hpp>

class AudioComp : public Component
{
    public:
        AudioComp(ObjectId id);
        void addSound(std::string key, sf::SoundBuffer* soundBuffer);
        void removeSound(std::string key);
        sf::SoundBuffer* getSound(std::string key);

    private:
        std::map<std::string, sf::SoundBuffer*> soundMap_;

};


#endif // AUDIOCOMP_H_INCLUDED
