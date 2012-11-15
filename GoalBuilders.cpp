#include "GoalBuilders.h"
#include "Goal.h"

Goal* makeMoveGoal(Parameters args)
{
    int source = atoi(args[1].c_str());
    int target = atoi(args[2].c_str());
    GoalMoveToTarget* goal = new GoalMoveToTarget(source, target);
    return goal;
}



Goal* makeWaitGoal(Parameters args)
{
    std::cout << "len paramMap: " << args.size() << std::endl;

    int waitTime = atoi(args[1].c_str());
    std::cout << "Wait time: " << args[1] << std::endl;
    GoalWait* goal = new GoalWait(waitTime);
    return goal;
}
