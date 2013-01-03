#ifndef PATHCOMP_H_INCLUDED
#define PATHCOMP_H_INCLUDED

#include "Components.h"
#include "TypeDefs.h"


class PathComp : public Component
{
    public:
        PathComp(ObjectId id);
        void setPath(Path* path);
        Path* getPath();
        Vector2d getNode();
        void nextNode();
        bool isAtEnd();


    private:
        Path* path_;
        Path::iterator iPath_;

};





#endif // PATHCOMP_H_INCLUDED
