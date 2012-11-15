#include "AiComp.h"
#include "Store.h"
#include "Goal.h"


AiComp::AiComp(ObjectId id) : Component(id, cType::Ai)
{
    std::cout << "Creating AiComp" << std::endl;
}

AiComp::~AiComp()
{
    clearGoal();
}


void AiComp::setGoal(Goal* goal)
{
    goal_ = goal;
}


void AiComp::clearGoal()
{
    goal_->del();
    delete(goal_);
    goal_ = NULL;
}


Goal* AiComp::getGoal()
{
    return goal_;
}
