#include "MusicPlayer.h"

#include "Core.h"

MusicPlayer::MusicPlayer(Core* core)
{
    core_ = core;
//    cumulativeElapsed_=0.0;
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
        cumulativeElapsed_ = 0;
        timeSliceNum_ = 0;
        runningTot_ = 0;
        profileMusic_();

        return true;
    }


    return false;
}



void MusicPlayer::profileMusic_()
{
    //clear any previous variables
    timeSlices_.clear();
    std::vector<short> buffer;
    std::cout << "Profiling music" << std::endl;
    //get music meta data
    int numSamples = musicBuffer_.GetSamplesCount();
    int duration = musicBuffer_.GetDuration();
    float samplesPerSecond = numSamples / duration;


    //transfer binary data into buffer
    std::copy(musicBuffer_.GetSamples(), musicBuffer_.GetSamples()+numSamples, std::back_inserter(buffer));

    //set moving window length and step size
    stepsPerSecond_ = 10;
    int windowLength = samplesPerSecond * 0.2; //1 second
    int stepSize = samplesPerSecond / stepsPerSecond_; //0.1 second
    std::cout << "SamplesPerSecond: " << samplesPerSecond << std::endl;
    std::cout << "StepSize        : " << stepSize << std::endl;
    double stepLengthInSeconds = samplesPerSecond / stepSize;
    std::cerr << "StepLenSeconds  : " << stepLengthInSeconds << std::endl;

    //set first time slice to begin + 0.5 * winLength in to track
    double stepsInOneWindow = double(windowLength) / double(stepSize);
    double stepsToMoveInToTrack = stepsInOneWindow/2.0;
    std::cerr << "Steps to move in: " << stepsToMoveInToTrack << std::endl;
    std::vector<double> rawWindowBuffer;
    for (int x=0;x<stepsToMoveInToTrack; ++x)
    {
        rawWindowBuffer.push_back(0.0);
    }
//    timeSliceNum_ = stepsToMoveInToTrack;


//    int dump; std::cin >> dump;
    //load window data into memory

    std::vector<double> rawWindowTot;
    for (int b=0;b<buffer.size()-windowLength;b+=stepSize)
    {
        double windowTotal = 0;
        double totSq=0.0;
        for(int w=b;w<b+windowLength;++w)
        {
            totSq+=pow(buffer[w]/10.0,2.0);
//            double addToTot = sqrt(pow(buffer[w]/10.0,2));

//            std::cout << w <<"\t" << addToTot << "\t" << windowTotal << "\t" << windowTotal / (w-b+1) << std::endl;
        }
        double meanSq = totSq/numSamples;
        double rmSq = sqrt(meanSq);
        rawWindowBuffer.push_back(rmSq);
    }

    //determine average value of all windows
    std::vector<double>::iterator iWin = rawWindowBuffer.begin();
    double totalOfAverages = 0;
    while(iWin!=rawWindowBuffer.end())
    {
        *iWin=pow(*iWin,2.0);
        totalOfAverages+=*iWin;
        ++iWin;
    }

    float baddies = 3.0 * duration;
    iWin = rawWindowBuffer.begin();
    while (iWin!=rawWindowBuffer.end())
    {
        *iWin = *iWin/(totalOfAverages/baddies);
        ++iWin;
    }


//    std::vector<double>::iterator iVal = cumulativeDiffBuffer.begin();
    float timeStamp = 0;
    for (int x=0;x<rawWindowBuffer.size();++x)
    {
        timeStamp = timeStamp + (windowLength / samplesPerSecond) / (samplesPerSecond/stepSize);
    }
//    while(iVal!=cumulativeDiffBuffer.end())
//    {
//        output << timeStamp << "\t" << *iVal << std::endl;
//        ++iVal;
//        timeStamp = timeStamp + (windowLength / samplesPerSecond) / (samplesPerSecond/stepSize);
//    }
    timeSlices_ = rawWindowBuffer;
    std::cout << "Duration: " << musicBuffer_.GetDuration() << std::endl;
//    exit(EXIT_FAILURE);


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
//    clock_t currTime = clock();

    int totalBaddies = 0;
//    std::cerr << timeSliceNum_<< "\t" << cumulativeElapsed_ << "\t+\t" << elapsed << "\t= ";
    cumulativeElapsed_+=elapsed;
//    std::cerr << cumulativeElapsed_<< "\n";
    for (int x=0; x<timeSlices_[timeSliceNum_]*50; ++x)
    {
        std::cout << "*";
    }
    std::cout << std::endl;
//    << timeSlicestimeSliceNum_] <<std::endl;
    while(cumulativeElapsed_>1.0/stepsPerSecond_)
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
            params["Object.Move.y"]="5";//ySpeed.str();
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
        cumulativeElapsed_ -=1.0/stepsPerSecond_;
    }
}



