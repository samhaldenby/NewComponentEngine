#ifndef GOAL_H_INCLUDED
#define GOAL_H_INCLUDED

#include <list>

class Core;

//////////
//builders

namespace gStatus
{
    enum{
            Done=1,
            Working=2,
            Failed=3,
            NotStarted=4
        };

}

typedef unsigned short GoalStatus;


//A Goal can be thought of as a node in a tree
class Goal
{
    public:
        Goal();
        virtual void carryOut()=0;
        GoalStatus getStatus();
        void setStatus(GoalStatus g);
        virtual void del();

        static Core* getCore();
        static void setCore(Core* core);

    private:
        static Core* core_;
        GoalStatus status_;
        virtual void onCommence_();
        virtual void onDone_();
        virtual void onFail_();

};


class GoalGroup : public Goal
{
    public:
        GoalGroup(std::list<Goal*> goals);
        void carryOut();
        void del();
    private:
        void nextGoal();
        std::list<Goal*> goals_;

//        void onCommence_();
//        void onDone_();
//        void onFail_();
};


class GoalMoveToTarget : public Goal
{
    public:
        GoalMoveToTarget(int s, int d);
        void carryOut();
    private:
        int targetId_;
        int sourceId_;

        void onCommence_();
        void onDone_();
        void onFail_();
};


class GoalWait : public Goal
{
    public:
        GoalWait(int w);
        void carryOut();
    private:
        int waitTimeLeft_;

        void onCommence_();
        void onDone_();
        void onFail_();
};


#endif // GOAL_H_INCLUDED
