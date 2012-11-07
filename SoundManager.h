#ifndef SOUNDMANAGER_H_INCLUDED
#define SOUNDMANAGER_H_INCLUDED

#include <SFML/Audio.hpp>

class SoundManager
{
    public:
        SoundManager();
        void playSound(sf::SoundBuffer* soundBuffer, bool isProtected=false);

        int getNextPlayerNum();
    private:
        std::vector<sf::Sound> soundInstances_;
        std::vector<sf::Sound> protectedSoundInstances_;
        int nextPlayer_;
};


#endif // SOUNDMANAGER_H_INCLUDED
