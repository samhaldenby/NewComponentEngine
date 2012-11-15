#include "Goal.h"
#include <iostream>


Core* Goal::core_ = NULL;

////////////
// Goal
Goal::Goal()
{
    std::cout << "Goal::Goal()" << std::endl;
    status_ = gStatus::NotStarted;
}


GoalStatus Goal::getStatus()
{
    return status_;
}


Core* Goal::getCore()
{
    return Goal::core_;
}


void Goal::setCore(Core* core)
{
    core_ = core;
}


void Goal::del()
{

}

void Goal::setStatus(GoalStatus g)
{
    GoalStatus prevStatus = status_;
    status_ =g;

    if (prevStatus == gStatus::NotStarted &&
        status_    == gStatus::Working)
    {
        onCommence_();
    }
    else if(status_ == gStatus::Done)
    {
        onDone_();
    }
    else if(status_ == gStatus::Failed)
    {
        onFail_();
    }
}


void Goal::onCommence_() {};
void Goal::onFail_() {};
void Goal::onDone_() {};

////////////
// GoalGroup
GoalGroup::GoalGroup(std::list<Goal*> goalList) : Goal()
{
    std::cout << "GoalGroup::GoalGroup(" << &goalList << ")" << std::endl;
    goals_ = goalList;
}



void GoalGroup::del()
{
    std::list<Goal*>::iterator iGoal = goals_.begin();
    while(iGoal!=goals_.end())
    {
        (*iGoal)->del();
        delete(*iGoal);
        ++iGoal;
    }
}
void GoalGroup::carryOut()
{
//    std::cout << "GoalGroup::carryOut()" << std::endl;
    if (goals_.size() == 0)
    {
        setStatus(gStatus::Done);
//        std::cout << ">No goals left. Returning" << std::endl;
        return;
    }

//    std::cout << ">Is first goal in list completed?" << std::endl;
    Goal* currentGoal = goals_.front();

    while(currentGoal->getStatus() == gStatus::Done)
    {
//        std::cout << ">>Goal met" << std::endl;
        goals_.pop_front();
//        std::cout << ">>>Removing first goal from list" << std::endl;
        if(goals_.size()==0)
        {
//            std::cout << ">>>No Goals Remaining" << std::endl;
            setStatus(gStatus::Done);
            return;
        }
        else
        {
//            std::cout << ">>>More Goals To Process" << std::endl;
            currentGoal = goals_.front();
        }
    }

    //check if goal failed
    if(currentGoal->getStatus() == gStatus::Failed)
    {
//        std::cout << ">>Goal has failed. Time to replan" << std::endl;
        setStatus(gStatus::Failed);
        return;
    }

    //carry out goal
//    std::cout << ">>Carrying out goal" << std::endl;
    currentGoal->carryOut();
}


////////////
// GoalMovetoTarget
GoalMoveToTarget::GoalMoveToTarget(int s, int d) : Goal()
{
    std::cout << "GoalMoveToTarget::GoalMoveToTarget(" << s << "," << d << ")" << std::endl;
    sourceId_ = s;
    targetId_ = d;
}

void GoalMoveToTarget::carryOut()
{
//    std::cout << "GoalMoveToTarget::CarryOut()" << std::endl;

    if (getStatus()==gStatus::NotStarted)
    {
        setStatus(gStatus::Working);
    }


    if (sourceId_ > targetId_)
    {
        sourceId_-=1;
    }
    else if (sourceId_ < targetId_)
    {
        sourceId_+=1;
    }

    if (sourceId_ == targetId_)
    {
        setStatus(gStatus::Done);
    }


    std::cout << "S vs T is now " << sourceId_ << " vs " << targetId_ << std::endl;

}


void GoalMoveToTarget::onCommence_()
{
    std::cout << "\033[034mCommencing move towards target\033[0m" << std::endl;
}

void GoalMoveToTarget::onDone_()
{
    std::cout << "\033[032mTarget has been reached!\033[0m" << std::endl;
}

void GoalMoveToTarget::onFail_()
{
    std::cout << "\033[031mFailed to move to target\033[0m" << std::endl;
}
////////////
// GoalWait
GoalWait::GoalWait(int w) : Goal()
{
    std::cout << "GoalWait::GoalWait(" << w << ")" << std::endl;
    waitTimeLeft_ = w;
}





void GoalWait::carryOut()
{
    if (getStatus()==gStatus::NotStarted)
    {
        setStatus(gStatus::Working);
    }



    if (waitTimeLeft_ > 0)
    {
        waitTimeLeft_ -=1;
    }
    else
    {
        setStatus(gStatus::Done);
    }


    std::cout << "Wait time is now " << waitTimeLeft_ << std::endl;

}


void GoalWait::onCommence_()
{
    std::cout << "\033[034mCommencing waiting\033[0m" << std::endl;
}

void GoalWait::onDone_()
{
    std::cout << "\033[032mWaiting completed!\033[0m" << std::endl;
}

void GoalWait::onFail_()
{
    std::cout << "\033[031mFailed to wait\033[0m" << std::endl;
}
