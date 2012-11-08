#include "AiComp.h"
#include "Store.h"


AiComp::AiComp(ObjectId id) : Component(id, cType::Ai)
{
    std::cout << "Creating AiComp" << std::endl;
}


void AiComp::addGoal(Goal* goal)
{
    goals_.push(goal);
}


void AiComp::nextGoal()
{
    goals_.pop();
}



void AiComp::clearGoals()
{
    std::queue<Goal*> emptyQ;
    goals_ = emptyQ;
}



Goal* AiComp::getCurrentGoal()
{
    return goals_.front();
}
