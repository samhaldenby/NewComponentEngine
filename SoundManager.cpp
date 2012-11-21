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
        protectedSoundInstances_.push_back(sf::Sound());
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



bool SoundManager::loadMusic(std::string fileName)
{

    if(musicBuffer_.LoadFromFile(fileName))
    {
        music_.SetBuffer(musicBuffer_);
        return true;
    }



    return false;
}


void SoundManager::analyseMusic()
{
    int steps =musicBuffer_.GetSamplesCount();
    std::cout << "STEPS: " << steps << std::endl;
    std::copy(musicBuffer_.GetSamples(), musicBuffer_.GetSamples()+steps, std::back_inserter(soundChunks_));
//    std::vector<short> soundChunks_ = musicBuffer_.GetSamples();


//     	Sound (const SoundBuffer &Buffer, bool Loop=false, float Pitch=1.f, float Volume=100.f, const Vector3f &Position=Vector3f(0, 0, 0))
//    ///AUDIO TEST
    std::cout << "BufferSize: " << soundChunks_.size() << std::endl;
    int duration = musicBuffer_.GetDuration();
    std::cout << "duration  : " << musicBuffer_.GetDuration() << std::endl;
    std::cout << "samples per second = " << soundChunks_.size() / musicBuffer_.GetDuration() << std::endl;
//    int dump;
//    std::cin >> dump;

    std::ofstream outSound;
    outSound.open("sound.txt");
    //int winLen = 44100;
    int winLen = 44100;
    int stepSize = 4410;
    std::vector<double> rawVec;
    for (int x=0;x<soundChunks_.size()-winLen; x+=stepSize)

    //10th of a second
    {

     double totalSq=0;
        for (int y=x; y< x+winLen; ++y)
        {

//        std::cout << soundChunks_[x] << "\t";
         //total += soundChunks_[y];
         totalSq+= soundChunks_[y]/10*soundChunks_[y]/10;


        }
//         std::cout << "TotalSq: " << totalSq << std::endl;
        double meanSq = double(totalSq)/(double(soundChunks_.size()));
     //   std::cout << "MeanSq : " << int(meanSq) << std::endl;
        double rmsq = sqrt(meanSq);
        rawVec.push_back(rmsq);
       // std::cout << "RMS    : " << int(rmsq) << std::endl;

       outSound << float(x)/44100.f << "\t" << rmsq << std::endl;

    }

    //calculate total
    long total = 0;
    std::vector<double>::iterator iChunk = rawVec.begin();

    while(iChunk!=rawVec.end())
    {
        std::cout << *iChunk << "\t";
        *iChunk= pow(*iChunk,3);

        std::cout << *iChunk << "\n";
                ++iChunk;
    }

    iChunk=rawVec.begin();
    while(iChunk!=rawVec.end())
    {
        total+=*iChunk++;
//        std::cout << total << ",";

    }
//    std::cout << "total: " << total;
//    std::cin >> dump;

    //convert raw to proportion
    iChunk = rawVec.begin();
//    while(iChunk!=rawVec.end())
//    {
//        *iChunk/=total;
//        *iChunk*=300.f;
//        *iChunk = *iChunk * *iChunk * *iChunk;
//        iChunk*=300.f;
//        ++iChunk;
//    }
    float baddies = 3*duration;
    while(iChunk!=rawVec.end())
    {
        *iChunk=*iChunk/(total/baddies);
//        *iChunk*;
        ++iChunk;
    }

    //now, calculate 5s window
   // 44100 * 5 = 225000;

//    //calc runing total
//    for (int x=0;x<rawVec.size();++x)
//    {
//        if (x!=0)
//        {
//            rawVec[x]+=rawVec[x-1];
//        }
//    }
    double runningTot=0.0;

//    //multiply by 300
//    iChunk = rawVec.begin();
//    while(iChunk!=rawVec.end())
//    {
//        *iChunk*=300.f;
//        ++iChunk;
//    }
//
//    //root it
//    iChunk = rawVec.begin();
//    while(iChunk!=rawVec.end())
//    {
//        *iChunk = (*iChunk) * *iChunk * *iChunk;
//        ++iChunk;
//    }
//
//    // x300
//    iChunk = rawVec.begin();
//    while(iChunk!=rawVec.end())
//    {
//        *iChunk*=300.f;
//        ++iChunk;
//    }



    outSound.close();








    //start music playing, and start clock()
//    sf::Sound sound;
//    sound.SetBuffer(musicBuffer_);
    music_.Play();
    clock_t prevTime = clock();
    std::cout << "Volume: " << music_.GetVolume() << std::endl;
}
void analyseMusic();
