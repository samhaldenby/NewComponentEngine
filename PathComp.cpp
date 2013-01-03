 #include "PathComp.h"

PathComp::PathComp(ObjectId id): Component(id, cType::Path)
{
    std::cout << "Creating PathComp" << std::endl;
    path_ = NULL;
    iPath_ = path_->begin();
}


 void PathComp::setPath(Path* path)
 {
     path_ = path;

     //set iterator to first node of path
     iPath_ = path_->begin();
 }



 Path* PathComp::getPath()
 {
     return path_;
 }



 Vector2d PathComp::getNode()
 {
     return *iPath_;
 }



 void PathComp::nextNode()
 {
     ++iPath_;
 }



bool PathComp::isAtEnd()
{
    return (iPath_==path_->end());
}
