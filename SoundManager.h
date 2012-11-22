#ifndef SOUNDMANAGER_H_INCLUDED
#define SOUNDMANAGER_H_INCLUDED

#include <SFML/Audio.hpp>

class SoundManager
{
    public:
        SoundManager();
        void playSound(sf::SoundBuffer* soundBuffer, bool isProtected=false);

        bool loadMusic(std::string fileName);
        void analyseMusic();

        int getNextPlayerNum();

        double getNextChunk();
    private:
        std::vector<sf::Sound> soundInstances_;
        std::vector<sf::Sound> protectedSoundInstances_;

        //for music
        sf::Sound music_;
        sf::SoundBuffer musicBuffer_;
        std::vector<short> soundChunks_;
        std::vector<double>processedChunks_;
        int nextPlayer_;

        int currChunk_;
};


#endif // SOUNDMANAGER_H_INCLUDED
