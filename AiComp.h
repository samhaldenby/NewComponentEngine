#ifndef AICOMP_H_INCLUDED
#define AICOMP_H_INCLUDED

#include <queue>
#include "Components.h"
#include "TypeDefs.h"

class Goal;

class AiComp : public Component
{
    public:
        AiComp(ObjectId id);
        void addGoal(Goal* goal);
        void nextGoal();
        void clearGoals();
        Goal* getCurrentGoal();
    private:

        std::queue<Goal*> goals_;


};


#endif // AICOMP_H_INCLUDED
