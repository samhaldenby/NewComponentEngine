#ifndef AICOMP_H_INCLUDED
#define AICOMP_H_INCLUDED

#include "Components.h"
#include "TypeDefs.h"

class Goal;

class AiComp : public Component
{
    public:
        AiComp(ObjectId id);
        ~AiComp(); //TODO: CHECK DESTRUCTOR WORKS!
        void setGoal(Goal* goal);
        void clearGoal();
        Goal* getGoal();
    private:

        Goal* goal_;


};


#endif // AICOMP_H_INCLUDED
