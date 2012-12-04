#include <iostream>
#include "TypeDefs.h"

#include "SoundManager.h"
#include <math.h>
SoundManager::SoundManager()
{
    std::cout << "Generating SoundManager" << std::endl;

    //create sound instances
    for (int c=0; c< MAX_CONCURRENT_SOUNDS/2; ++c)
    {
        soundInstances_.push_back(sf::Sound());
        soundInstances_[c].SetVolume(50);
        protectedSoundInstances_.push_back(sf::Sound());
        soundInstances_[c].SetVolume(50);
    }


    nextPlayer_ =0;

    std::cout << "Created with " << soundInstances_.size() + protectedSoundInstances_.size() << " max concurrent sounds" << std::endl;
}

int SoundManager::getNextPlayerNum()
{
    return nextPlayer_;
}

void SoundManager::playSound(sf::SoundBuffer* soundBuffer, bool isProtected)
{
    if(soundBuffer==NULL)
    {
        std::cout << "No sound buffer sent" << std::endl;
        return;
    }

    if (isProtected)
    {
        std::vector<sf::Sound>::iterator iSound = protectedSoundInstances_.begin();
        while(iSound!=protectedSoundInstances_.end())
        {
            if(iSound->GetStatus()==sf::Sound::Stopped)
            {
                iSound->SetBuffer(*soundBuffer);
                iSound->Play();
                return;
            }
            ++iSound;
        }
        std::cout << "NO FREE PROTECTED SOUND BUFFERS!" << std::endl;
    }
    else if (!isProtected)
    {
        std::cout << "NextPlayer = " << nextPlayer_ << " vs size of playerVector: " << soundInstances_.size() << std::endl;
        soundInstances_[nextPlayer_].SetBuffer(*soundBuffer);
        soundInstances_[nextPlayer_].Play();

        if(++nextPlayer_==(MAX_CONCURRENT_SOUNDS/2))
        {
            nextPlayer_=0;
        }

    }

};


