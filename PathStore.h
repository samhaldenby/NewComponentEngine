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







#endif // PATHSTORE_H_INCLUDED
