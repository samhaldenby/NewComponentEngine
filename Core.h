#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include "ObjectStore.h"
#include "Store.h"

#include "Systems.h"
#include "AiComp.h"
#include "AnchorComp.h"
#include "AudioComp.h"
#include "HealthComp.h"
#include "NameComp.h"
#include "CoordsComp.h"
#include "MoveComp.h"
#include "EventComp.h"
#include "GfxComp.h"
#include "LauncherComp.h"
#include "CollisionComp.h"
#include "ObjectBuilder.h"


#include <string>



class Store;
class ObjectBuilder;
class ObjectStore;
class MessageCentre;
class Ui;


//@@@Requires updating on addition on new subsystem" when adding new subsystems
class Core
{
    public:
        Core(std::string coreConfigFileName);
        Store*              getStore();
        ObjectBuilder*      getObjectBuilder();
        ObjectStore*        getObjectStore();
        MessageCentre*      getMessageCentre();
        Ui*                 getUi();

        System<HealthComp>* getHealthSub();
        System<NameComp>*   getNameSub();
        System<CoordsComp>* getCoordsSub();
        System<MoveComp>*   getMoveSub();
        System<GfxComp>*    getGfxSub();
        System<AiComp>*     getAiSub();
        System<AnchorComp>* getAnchorSub();
        System<AudioComp>*  getAudioSub();
        System<LauncherComp>* getLauncherSub();
        System<CollisionComp>* getCollisionSub();
        System<EventComp>* getEventSub();



    private:
        System<HealthComp>* healthSub_;
        System<NameComp>*   nameSub_;
        System<CoordsComp>* coordsSub_;
        System<MoveComp>*   moveSub_;
        System<GfxComp>*    gfxSub_;
        System<AiComp>*     aiSub_;
        System<AnchorComp>* anchorSub_;
        System<AudioComp>*  audioSub_;
        System<LauncherComp>* launcherSub_;
        System<CollisionComp>* collisionSub_;
        System<EventComp>* eventSub_;

        Store* store_;
        ObjectBuilder* objectBuilder_;
        ObjectStore* objectStore_;
        MessageCentre* messageCentre_;
        Ui* ui_;
};
//class Core
//{
//    private:
//        Store* store_;
//        ObjectStore* objectStore_;
//
//        //Systems
//        System<HealthComp>* healthSub;
//        System<NameComp>*   nameSub;
//
//    public:
//        Store* getStore()
//        {
//            return store_;
//        }
//
//        ObjectStore* getObjectStore()
//        {
//            return objectStore_;
//        }
//};

#endif // CORE_H_INCLUDED
