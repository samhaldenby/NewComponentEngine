#include "ObjectBuilder.h"
#include "ObjectStore.h"
#include "Core.h"
#include "Store.h"
#include "Telegram.h"
#include "MessageCentre.h"


#include "Object.h"

ObjectBuilder::ObjectBuilder(Core* core) : core_(core)
{
    Object::setCore(core);
}


//@@@Requires updating on addition on new subsystem" when adding new subsystems
ObjectId ObjectBuilder::createObject(std::string blueprintName)
{
    //fetch blueprint
    Blueprint* blueprint = core_->getStore()->getBlueprint(blueprintName);
    if(!blueprint)
    {
        std::cout << "Unable to fetch blueprint: " << blueprintName << std::endl;
        return -1;
    }

    //grab name
    bool hasName = blueprint->get("Object.Name",false);
    std::string name = blueprint->get("Object.Name","NO NAME");
    //check for gfx
    bool hasGfx = blueprint->get("Object.Gfx",false);
//    bool hasCollision = blueprint->get("Object.Collision",false);
    bool hasCoords = blueprint->get("Object.Coords",false);
//    bool hasSfx = blueprint->get("Object.Sfx", false);
    bool hasHealth = blueprint->get("Object.Health", false);
    bool hasMove = blueprint->get("Object.Move", false);
    bool hasLauncher = blueprint->get("Object.Launcher",false);
    bool hasCollision = blueprint->get("Object.Collision",false);
//    bool hasInput = blueprint->get("Object.Input", false);
//    bool hasOnSelect = blueprint->get("Object.OnSelect", false);

    std::cout << "_______________________________________________" << std::endl;
    std::cout << "Creating object instance of " << name << std::endl;
    std::cout << (hasGfx ? "has" : "does not have") << " Gfx" << std::endl;
//    std::cout << (hasCoords ? "has" : "does not have") << " Coords" << std::endl;
//    std::cout << (hasCollision ? "has" : "does not have") << " Collision" << std::endl;
//    std::cout << (hasSfx ? "has" : "does not have") << " Sfx" << std::endl;
    std::cout << (hasHealth ? "has" : "does not have") << " Health " << std::endl;
    std::cout << (hasMove ? "has" : "does not have") << " Move " << std::endl;
    std::cout << (hasName ? "has" : "does not have") << " Name " << std::endl;
    std::cout << (hasLauncher ? "has" : "does not have") << " Launcher " << std::endl;
    std::cout << (hasCollision ? "has" : "does not have") << " Collision " << std::endl;
//    std::cout << (hasInput ? "has" : "does not have") << " Input " << std::endl;
//    std::cout << (hasOnSelect ? "has" : "does not have") << " OnSelect " << std::endl;

    //create object
    int objectId = core_->getObjectStore()->addObject();
    Object* object = core_->getObjectStore()->getObject(objectId);
    //build modules
    if(hasGfx)
    {
        object->addFlag(cFlag::Gfx);
        core_->getGfxSub()->addComponent(objectId);
        GfxComp* gfx = core_->getGfxSub()->getComponent(objectId);
        //send message to update graphics
        Parameters changeGfxParams;
        changeGfxParams.push_back("gfx");
        changeGfxParams.push_back("changeSprite");
        changeGfxParams.push_back(blueprint->get("Object.Gfx.Sprite", ""));
        Message message(gfx->getId(), gfx->getId(), changeGfxParams);
        Telegram telegram(gfx->getId(),gfx->getId(), 0.0, message);
        core_->getMessageCentre()->addTelegram(telegram);
//        gfx->setSprite(blueprint->get("Object.Gfx.Sprite", ""));
    }

//    if(hasCollision)
//    {
//        object->addFlag(cFlag::Collision);
//        core_->getCollisionSub()->addComponent(objectId);
//        CollisionComponent* collision = core_->getCollisionSub()->getComponent(objectId);
//    }
//
    if(hasName)
    {
        object->addFlag(cFlag::Name);
        core_->getNameSub()->addComponent(objectId);
        NameComp* name = core_->getNameSub()->getComponent(objectId);
        name->setName(blueprint->get("Object.Name","NO NAME"));
    }
    if(hasCoords)
    {
        object->addFlag(cFlag::Coords);
        core_->getCoordsSub()->addComponent(objectId);
        CoordsComp* coords = core_->getCoordsSub()->getComponent(objectId);
        coords->setCoords(Vector2d(blueprint->get("Object.Coords.x",0.f) , blueprint->get("Object.Coords.y",0.f)));
    }

    if(hasHealth)
    {
        object->addFlag(cFlag::Health);
        core_->getHealthSub()->addComponent(objectId);
        HealthComp* health = core_->getHealthSub()->getComponent(objectId);
        health->setMax(blueprint->get("Object.Health.Max", 0));
        health->setCurrent(blueprint->get("Object.Health.Current", 0));
    }

    if(hasMove)
    {
        object->addFlag(cFlag::Move);
        core_->getMoveSub()->addComponent(objectId);
        MoveComp* move = core_->getMoveSub()->getComponent(objectId);
        move->setMove(Vector2d(blueprint->get("Object.Move.x",0.f), blueprint->get("Object.Move.y",0.f)));
    }

    if(hasLauncher)
    {
        object->addFlag(cFlag::Launcher);
        core_->getLauncherSub()->addComponent(objectId);
        LauncherComp* launcher = core_->getLauncherSub()->getComponent(objectId);
        launcher->setMaxCooldown(blueprint->get("Object.Launcher.MaxCooldown",0.f));
        launcher->setProjectileBlueprintName(blueprint->get("Object.Launcher.Projectile",""));
    }

    if(hasCollision)
    {
        object->addFlag(cFlag::Collision);
        core_->getCollisionSub()->addComponent(objectId);
        CollisionComp* launcher = core_->getCollisionSub()->getComponent(objectId);
    }


    return objectId;
//
//    if(hasInput)
//    {
//        object->addFlag(cFlag::Input);
//        core_->getInputSub()->addComponent(objectId);
//        InputComponent* input = core_->getInputSub()->getComponent(objectId);
//    }
//
//    if(hasOnSelect)
//    {
//        object->addFlag(cFlag::OnSelect);
//        core_->getOnSelectSub()->addComponent(objectId);
//        OnSelectComponent* onSelect = core_->getOnSelectSub()->getComponent(objectId);
//        onSelect->setCommand(blueprint->get("Object.OnSelect.Command",""));
//    }
//
//
//    std::cout << object->hasFlag(cFlag::Gfx) << "\t" << object->hasFlag(cFlag::Coords) << "\t" << object->hasFlag(cFlag::Stats) << std::endl;
}
