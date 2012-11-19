#ifndef GOAL_H_INCLUDED
#define GOAL_H_INCLUDED

#include "Message.h"

class Core;


class Goal : public Message
{
    public:
        Goal(ObjectId sourceId, ObjectId targetId, Parameters params);
        virtual bool met() = 0;
        virtual void act() = 0;
//        Core* getCore();

};

class GoalApproach : public Goal
{
    public:
        GoalApproach(ObjectId sourceId, ObjectId targetId, Parameters params);
        bool met();
        void act();
    private:
        double minDistToTarget_;
};


#endif // GOAL_H_INCLUDED
