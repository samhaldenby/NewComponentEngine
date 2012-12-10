#include "MusicPlayer.h"

#include "Core.h"

MusicPlayer::MusicPlayer(Core* core)
{
    core_ = core;
}

void MusicPlayer::addRespondingObject(ObjectId id)
{
    respondingObjects_.insert(id);
}

void MusicPlayer::removeRespondingObject(ObjectId id)
{
    respondingObjects_.erase(id);
}

bool MusicPlayer::loadMusic(std::string fileName)
{

    if(musicBuffer_.LoadFromFile(fileName))
    {
        music_.SetBuffer(musicBuffer_);
        timeSliceNum_ = 0;
        runningTot_ = 0;
        cumulativeElapsed_ = 0;
        profileMusic_();
        return true;
    }


    return false;
}




void MusicPlayer::profileMusic_()
{


    timeSlices_.clear();
    std::vector<short> myBuffer;
    int steps =musicBuffer_.GetSamplesCount();
    std::cout << "Steps    : " << steps << std::endl;
    std::copy(musicBuffer_.GetSamples(), musicBuffer_.GetSamples()+steps, std::back_inserter(myBuffer));
//    std::vector<short> myBuffer = musicBuffer_.GetSamples();


//     	Sound (const SoundBuffer &Buffer, bool Loop=false, float Pitch=1.f, float Volume=100.f, const Vector3f &Position=Vector3f(0, 0, 0))
//    ///AUDIO TEST
    std::cerr << "BufferSize: " << myBuffer.size() << std::endl;
    int duration = musicBuffer_.GetDuration();
    std::cerr << "Duration  : " << musicBuffer_.GetDuration() << std::endl;
    std::cerr << "SampleRate: " << musicBuffer_.GetSampleRate() << std::endl;

    std::cerr << "samples per second = " << myBuffer.size() / musicBuffer_.GetDuration() << std::endl;
    int samplesPerSecond = myBuffer.size() / musicBuffer_.GetDuration();
//    exit(EXIT_FAILURE);
//    int dump;
//    std::cin >> dump;

//    std::ofstream outSound;
//    outSound.open("sound.txt");
    //int winLen = 44100;
    int winLen = samplesPerSecond/2;

    int stepSize = samplesPerSecond / 20;//4410;
//    std::vector<double> timeSlices_;
    for (int x=0;x<myBuffer.size()-winLen; x+=stepSize)

    //10th of a second
    {

        double totalSq=0;
        //grab window
        for (int y=x; y< x+winLen; ++y)
        {

//          std::cout << myBuffer[x] << "\t";
            //total += myBuffer[y];
            totalSq+= pow(myBuffer[y]/10,2);


        }
//         std::cout << "TotalSq: " << totalSq << std::endl;
        double meanSq = double(totalSq)/(double(myBuffer.size())); //TODO: Think this should probably be / winLen size
//        std::cerr << totalSq << " / " << winLen << " = " << double(totalSq)/double(winLen) << std::endl;
//        double meanSq = double(totalSq)/(double(winLen)); //TODO: Think this should probably be / winLen size
     //   std::cout << "MeanSq : " << int(meanSq) << std::endl;
     double rmsq = sqrt(meanSq);
        std::cerr << rmsq << std::endl;
        timeSlices_.push_back(rmsq);
       // std::cout << "RMS    : " << int(rmsq) << std::endl;

//       outSound << float(x)/44100.f << "\t" << rmsq << std::endl;

    }

    //calculate total
    long total = 0;
    std::vector<double>::iterator iChunk = timeSlices_.begin();

    while(iChunk!=timeSlices_.end())
    {
        std::cout << *iChunk << "\t";
        *iChunk= pow(*iChunk,3);

        std::cout << *iChunk << "\n";
                ++iChunk;
    }

    iChunk=timeSlices_.begin();
    while(iChunk!=timeSlices_.end())
    {
        total+=*iChunk++;
//        std::cout << total << ",";

    }


    //convert raw to proportion
    iChunk = timeSlices_.begin();

    float baddies = 3*duration;
    while(iChunk!=timeSlices_.end())
    {
        *iChunk=*iChunk/(total/baddies);

        ++iChunk;
    }


    double runningTot=0.0;



//    outSound.close();






      //  int dump;


    std::cout << "Volume: " << music_.GetVolume() << std::endl;
//        std::cin >> dump;

    std::cout << "TimeSlices: " << timeSlices_.size() << std::endl;
    std::cout << "TimeSlices/Second: " << timeSlices_.size() / musicBuffer_.GetDuration() << std::endl;
//    exit(EXIT_FAILURE);
    ///END AUDIO TEST
}



void MusicPlayer::play()
{
    music_.Play();
}



void MusicPlayer::update(double elapsed)
{
      ///TEST BADDIES
    //check clock()
//        std::cout << "Checking elapsed time for enemy creation" << std::endl;
    clock_t currTime = clock();
    cumulativeElapsed_+=elapsed;
    int totalBaddies = 0;
    std::cerr << timeSliceNum_<< "\telapsed: " << elapsed << "\t" << cumulativeElapsed_<<"\t";
    for (int x=0; x<timeSlices_[timeSliceNum_]*50; ++x)
    {
        std::cerr << "*";
    }
    std::cerr << std::endl;
//    << timeSlicestimeSliceNum_] <<std::endl;
    while(cumulativeElapsed_>0.05)
    {
        ++timeSliceNum_;
//        std::cout << cumulativeElapsed_<< ":\t" << timeSliceNum_ << "\t" << timeSlices_[timeSliceNum_] << "\n";
//        std::cout << timeSlices_.size() << std::endl;
//        std::cout << "RT: " << runningTot_ << std::endl;
        runningTot_+=timeSlices_[timeSliceNum_];
        while(runningTot_>1)
        {
            ++totalBaddies;
            std::cout << "Baddies : " << totalBaddies << std::endl;
            NamedParams params;

            std::stringstream xSS(""),ySpeed("");
            xSS << rand()%800;
            ySpeed << timeSlices_[timeSliceNum_]*50;//float(rand()%30+5.0)/5.0;
            std::cout << "Coords(" << xSS.str() << ",0)" << std::endl;
            params["Object.Coords.x"]=xSS.str();
            params["Object.Coords.y"]="0";
//            params["Object.Move"]="true";
            params["Object.Move.y"]=ySpeed.str();
            params["Object.Move.x"]="0";

            ObjectId id = core_->getObjectBuilder()->createObject("livingQuarters",params);
            addRespondingObject(id);

            runningTot_-=1;

        }

        //change speed of all responders
        std::stringstream speedSs("");
//        speedSs << timeSlices_[timeSliceNum_]*50;
        std::set<ObjectId>::iterator iObj = respondingObjects_.begin();
        while(iObj!=respondingObjects_.end())
        {
            //get move comp
            MoveComp* moveComp = core_->getMoveSub()->getComponent(*iObj);
            if(moveComp)
            {

                moveComp->setSpeed(timeSlices_[timeSliceNum_]*50);
                ++iObj;
            }
            else
            {
                respondingObjects_.erase(iObj++);
            }
        }


//        ObjectMap::iterator iEnemy = db.objectMap.begin();
//        while(iEnemy!=db.objectMap.end())
//        {
//            if(iEnemy->second!=NULL)
//            {
//                 if(iEnemy->second->isType(ClassType::Enemy))
//                 {
//                     iEnemy->second->velocity.y = timeSlices_[timeSlice]*1000;
//                 }
//            }
//            ++iEnemy;
//        }
        cumulativeElapsed_ -=0.05;

    }
}



