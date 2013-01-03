#ifndef PATHSTORE_H_INCLUDED
#define PATHSTORE_H_INCLUDED

#include "TypeDefs.h"

namespace pType
{
    enum{   Bezier = 1,
            Catmul = 2
        };
}

class PathStore
{
    public:
        PathStore();
        void setMaxPointsInSpline(int num);
        void setMaxNodes(int nodes);
        Path* getPath(int pathNum);
        void addPath(int pathNum, int pathType, int pathSeed);
    private:
        int maxPointsInSpline_;
        int maxNodes_;
        std::map<int, Path> paths_;


};


PathStore::PathStore()
{
    maxPointsInSpline_ = 4;
    maxNodes_ = 20;
}


void setMaxPointsInSpline(int num)
{
    maxPointsInSpline_ = num;
}


void setMaxNodes(int nodes)
{
    maxNodes_ = nodes;
}



Path* PathStore::getPath(int pathNum)
{
    std::map<int,Path>::iterator iPath = paths_.find(pathNum);
    if (iPath == paths_.end())
    {
        return NULL;
    }
    else
    {
        return &(iPath->second);
    }
}


void addPath(int pathNum, int pathType, int pathSeed)
{
    switch(pathType)
    {
        case pType::Bezier:
        {



#endif // PATHSTORE_H_INCLUDED
