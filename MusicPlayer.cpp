#include "MusicPlayer.h"

#include "Core.h"

MusicPlayer::MusicPlayer(Core* core)
{
    core_ = core;
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
    std::cout << "STEPS: " << steps << std::endl;
    std::copy(musicBuffer_.GetSamples(), musicBuffer_.GetSamples()+steps, std::back_inserter(myBuffer));
//    std::vector<short> myBuffer = musicBuffer_.GetSamples();


//     	Sound (const SoundBuffer &Buffer, bool Loop=false, float Pitch=1.f, float Volume=100.f, const Vector3f &Position=Vector3f(0, 0, 0))
//    ///AUDIO TEST
    std::cout << "BufferSize: " << myBuffer.size() << std::endl;
    int duration = musicBuffer_.GetDuration();
    std::cout << "duration  : " << musicBuffer_.GetDuration() << std::endl;
    std::cout << "samples per second = " << myBuffer.size() / musicBuffer_.GetDuration() << std::endl;
//    int dump;
//    std::cin >> dump;

    std::ofstream outSound;
    outSound.open("sound.txt");
    //int winLen = 44100;
    int winLen = 44100;
    int stepSize = 4410;
//    std::vector<double> timeSlices_;
    for (int x=0;x<myBuffer.size()-winLen; x+=stepSize)

    //10th of a second
    {

     double totalSq=0;
        for (int y=x; y< x+winLen; ++y)
        {

//        std::cout << myBuffer[x] << "\t";
         //total += myBuffer[y];
         totalSq+= myBuffer[y]/10*myBuffer[y]/10;


        }
//         std::cout << "TotalSq: " << totalSq << std::endl;
        double meanSq = double(totalSq)/(double(myBuffer.size()));
     //   std::cout << "MeanSq : " << int(meanSq) << std::endl;
        double rmsq = sqrt(meanSq);
        timeSlices_.push_back(rmsq);
       // std::cout << "RMS    : " << int(rmsq) << std::endl;

       outSound << float(x)/44100.f << "\t" << rmsq << std::endl;

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



    outSound.close();






      //  int dump;


    std::cout << "Volume: " << music_.GetVolume() << std::endl;
//        std::cin >> dump;


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
//    std::cout << "elapsed: " << cumulativeElapsed_<<"\n";
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
//            Enemy* p = new Enemy(&db);
//            GameObject* pAst =  p;
//            int xCo = rand()%int(db.screenDimensions.x-100) + 50;
//            pAst->coords = Vector2d(xCo, 70);
//            pAst->changeSprite("enemy_ship01");
//            p->maxHealth=20;
//            p->health = 20;
//            p->statSpeed = timeSlices_[timeSlice]*1000;
//            p->statShotCoolDown=float(rand())/RAND_MAX + 0.3;
//            p->statShotSpeed = float(p->statSpeed+200);
//
//            //create a meter
//            //create meter
////                Meter* pMeter =new Meter(p);
////                pMeter->dims = Vector2d(db.screenDimensions.x/10,5);
////                pMeter->coords = Vector2d(db.screenDimensions.x/40 , db.screenDimensions.y/40);
////                pMeter->anchored =true;
////                db.meterList.push_back(pMeter);
////                std::cout << "done" << std::endl;
//
////                pAst->velocity = Vector2d(rand()%100 -50,rand()%500 + 100);
//            pAst->velocity = Vector2d(rand()%200 -100,p->statSpeed);
            runningTot_-=1;

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



