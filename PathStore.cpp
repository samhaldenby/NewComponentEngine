#include "PathStore.h"
#include "SplineGenerator.h"

PathStore::PathStore()
{
    maxPointsInSpline_ = 40;
    maxNodes_ = 10;
}


void PathStore::setMaxPointsInSpline(int num)
{
    maxPointsInSpline_ = num;
}


void PathStore::setMaxNodes(int nodes)
{
    maxNodes_ = nodes;
}



Path* PathStore::getPath(int pathNum)
{
    std::map<int,Path>::iterator iPath = paths_.find(pathNum);
    if (iPath == paths_.end())
    {
        //create path - //TODO This defaults to a catmul - change so that it can be set dynamically to bezier or any other?
        addPath(pathNum, pType::Catmul,pathNum);
    }

    return &(paths_[pathNum]);

}


void PathStore::addPath(int pathNum, int pathType, int pathSeed=-1)
{
    if (pathSeed==-1)
    {
        pathSeed = pathNum;
    }

    switch(pathType)
    {
        case pType::Bezier:
        {
            paths_.insert(std::pair<int,Path>(pathNum, SplineGenerator::makeBezier(maxPointsInSpline_ , maxNodes_ , pathSeed)));
            break;
        }
        case pType::Catmul:
        {
            paths_.insert(std::pair<int,Path>(pathNum, SplineGenerator::makeCatmul(maxPointsInSpline_ , maxNodes_ , pathSeed)));
            break;
        }
        default:
            break;
    }
};
