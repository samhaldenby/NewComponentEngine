#ifndef MUSICPLAYER_H_INCLUDED
#define MUSICPLAYER_H_INCLUDED

#include <string>
#include "TypeDefs.h"
#include <SFML/Audio.hpp>

class Core;

class MusicPlayer
{
    public:
        MusicPlayer(Core* core);
        bool loadMusic(std::string fileName);
        void play();

        void addRespondingObject(ObjectId id);
        void removeRespondingObject(ObjectId id);

        void update(double elapsed);


    private:
        Core* core_;
        void profileMusic_();

        sf::Sound music_;
        sf::SoundBuffer musicBuffer_;

        std::vector<double> timeSlices_;

        int timeSliceNum_;

        double runningTot_;
        int stepsPerSecond_;

        double cumulativeElapsed_;

        std::set<ObjectId> respondingObjects_;




};





#endif // MUSICPLAYER_H_INCLUDED
