#include "Effect.h"
#include "Utils.h"

Effect::Effect(std::string effectString)
{
    hasDuration_ = false;

    //parse string
    //split on /
    StrTokens slashSplit = tokenise(effectString,'/');
    std::cout << "Len Tokens: " << slashSplit.size() <<std::endl;
    std::cout << "Begin : " << slashSplit[0]<< std::endl;
    std::cout << "Update: " << slashSplit[1]<< std::endl;
    std::cout << "End   : " << slashSplit[2]<< std::endl;
    std::cout << "Durat.: " << slashSplit[3]<< std::endl;
    setOnBegin(slashSplit[0]);
    setOnUpdate(slashSplit[1]);
    setOnEnd(slashSplit[2]);
    if(slashSplit[3]=="No Duration")
    {
        setDuration(NO_DURATION);
    }
    else
    {
        setDuration(atof(slashSplit[3].c_str()));
    }
}




void Effect::setOnBegin(std::string effectString)
{
    //split by ;

    Parameters scSplit = tokenise(effectString,'*');
    //split each message into parameters
    Parameters::iterator iMsg = scSplit.begin();
    while(iMsg!=scSplit.end())
    {
        onBeginParams_.push_back(tokenise(*iMsg,'_'));
        ++iMsg;
    }
};


void Effect::setOnUpdate(std::string effectString)
{
    //split by ;
    Parameters scSplit = tokenise(effectString,'*');
    //split each message into parameters
    Parameters::iterator iMsg = scSplit.begin();
    while(iMsg!=scSplit.end())
    {
        onUpdateParams_.push_back(tokenise(*iMsg,'_'));
        ++iMsg;
    }
};


void Effect::setOnEnd(std::string effectString)
{
    //split by ;
    Parameters scSplit = tokenise(effectString,'*');
    //split each message into parameters
    Parameters::iterator iMsg = scSplit.begin();
    while(iMsg!=scSplit.end())
    {
        onEndParams_.push_back(tokenise(*iMsg,'_'));
        ++iMsg;
    }
};


void Effect::setDuration(double duration)
{
    duration_ = duration;
    hasDuration_ = true;
}


void Effect::updateDuration(double elapsed)
{
    std::cout << "Duration of effect reduced from " << duration_ << " to ";
    duration_-=elapsed;
    std::cout << " duration" << std::endl;

}


bool Effect::hasDuration()
{

    return hasDuration_;
}


bool Effect::hasExpired()
{
    return (duration_<0);
}


std::vector<Parameters> Effect::getOnBegin()
{
    return onBeginParams_;
}


std::vector<Parameters> Effect::getOnUpdate()
{
    return onUpdateParams_;
}


std::vector<Parameters> Effect::getOnEnd()
{
    return onEndParams_;
}
