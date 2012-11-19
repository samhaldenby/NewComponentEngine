#include "ObjectBuilder.h"
#include "ObjectStore.h"
#include "Core.h"
#include "Store.h"
#include "Telegram.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include "MessageCentre.h"

#include "Utils.h"


#include "Object.h"

//@@@Update this function on adding new component types
ObjectBuilder::ObjectBuilder(Core* core) : core_(core)
{
    Object::setCore(core);

    //initialise component maker function map
    compMakerFnMap_["Name"]=&ObjectBuilder::addNameComp_;
    compMakerFnMap_["Gfx"]=&ObjectBuilder::addGfxComp_;
    compMakerFnMap_["Audio"]=&ObjectBuilder::addAudioComp_;
    compMakerFnMap_["Ai"]=&ObjectBuilder::addAiComp_;
    compMakerFnMap_["Coords"]=&ObjectBuilder::addCoordsComp_;
    compMakerFnMap_["Health"]=&ObjectBuilder::addHealthComp_;
    compMakerFnMap_["Move"]=&ObjectBuilder::addMoveComp_;
    compMakerFnMap_["Launcher"]=&ObjectBuilder::addLauncherComp_;
    compMakerFnMap_["Collision"]=&ObjectBuilder::addCollisionComp_;
    compMakerFnMap_["Events"]=&ObjectBuilder::addEventComp_;

}


//@@@Requires updating on addition on new subsystem" when adding new subsystems
ObjectId ObjectBuilder::createObject(std::string blueprintName, NamedParams additionalVars)
{
    //fetch blueprint
    Blueprint* blueprint = core_->getStore()->getBlueprint(blueprintName);
    if(!blueprint)
    {
        std::cout << "Unable to fetch blueprint: " << blueprintName << std::endl;
        return -1;
    }



    //If there are changes the original blueprint, make them but back up original values
    NamedParams backupParams;
    NamedParams::iterator iVar = additionalVars.begin();
    while (iVar!=additionalVars.end())
    {
        backupParams[iVar->first] = blueprint->get(iVar->first,"");

        std::cout << "Changing: " << iVar->first << " from " << backupParams[iVar->first] << " to " << iVar->second << std::endl;
        blueprint->put(iVar->first, iVar->second);
        ++iVar;
    }


    std::cout << "BLUEPRINT: " << blueprint << std::endl;
    //grab name
    bool hasName = blueprint->get("Object.Name",false);
    std::string name = blueprint->get("Object.Name","NO NAME");
    //check for gfx
    bool hasGfx = blueprint->get("Object.Gfx",false);
    bool hasAudio = blueprint->get("Object.Audio",false);
    bool hasAi = blueprint->get("Object.Ai",false);
//    bool hasCollision = blueprint->get("Object.Collision",false);
    bool hasCoords = blueprint->get("Object.Coords",false);
//    bool hasSfx = blueprint->get("Object.Sfx", false);
    bool hasHealth = blueprint->get("Object.Health", false);
    bool hasMove = blueprint->get("Object.Move", false);
    bool hasLauncher = blueprint->get("Object.Launcher",false);
    bool hasCollision = blueprint->get("Object.Collision",false);
    bool hasEvent = blueprint->get("Object.Events",false);
//    bool hasInput = blueprint->get("Object.Input", false);
//    bool hasOnSelect = blueprint->get("Object.OnSelect", false);

    std::cout << "_______________________________________________" << std::endl;
    std::cout << "Creating object instance of " << name << std::endl;
    std::cout << (hasGfx ? "has" : "does not have") << " Gfx" << std::endl;
    std::cout << (hasAudio ? "has" : "does not have") << " Audio" << std::endl;
    std::cout << (hasAi ? "has" : "does not have") << " Ai" << std::endl;
    std::cout << (hasEvent ? "has" : "does not have") << " Event" << std::endl;
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




    //iterate over ptree and build modules
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
                  blueprint->get_child("Object"))
    {
        std::string componentName = v.first.data();
//        std::string blueprintFileName = v.second.data();
        std::cout << "bp: " << componentName << std::endl;//"\t" << blueprintFileName << std::endl;
        //add component
        CompMakerFnMap::iterator iCompMakerFn = compMakerFnMap_.find(componentName);
        if(iCompMakerFn!=compMakerFnMap_.end())
        {
//            (this->*(compMakerFnMap_[componentName]))(objectId,object,(Blueprint*)(&v.second));
              (this->*(compMakerFnMap_[componentName]))(objectId,object,blueprint);
        }


    }



    //revert any changes
    iVar = backupParams.begin();
    while (iVar!=backupParams.end())
    {
//        backupParams[iVar->first] = blueprint->get(iVar->first,"");

//        std::cout << "Changing: " << iVar->first << " from " << backupParams[iVar->first] << " to " << iVar->second << std::endl;
        blueprint->put(iVar->first, iVar->second);
        ++iVar;
//        int dump; std::cin >> dump;
    }

    //run any onCreate events
    if (hasEvent)
    {
        Parameters onCreateParams;
        onCreateParams.push_back("event");
        onCreateParams.push_back("execute");
        onCreateParams.push_back("onCreate");

        Message onCreateMsg(objectId, objectId, onCreateParams);
        Telegram onCreateTelegram(objectId, objectId, 0.0, onCreateMsg);
        core_->getMessageCentre()->addTelegram(onCreateTelegram);
    }
    return objectId;

}


bool ObjectBuilder::addGfxComp_(ObjectId objectId, Object* object, Blueprint* blueprint)
{
        object->addFlag(cFlag::Gfx);
        core_->getGfxSub()->addComponent(objectId);
        GfxComp* gfx = core_->getGfxSub()->getComponent(objectId);
        //update graphics
        Parameters changeGfxParams;
        std::string imageName = blueprint->get("Object.Gfx.Sprite","");
        sf::Image* image = core_->getStore()->getImage(imageName);
        gfx->setSprite(image);

        return true;
}



bool ObjectBuilder::addAudioComp_(ObjectId objectId, Object* object, Blueprint* blueprint)
{
    object->addFlag(cFlag::Audio);
    core_->getAudioSub()->addComponent(objectId);
    AudioComp* audio = core_->getAudioSub()->getComponent(objectId);
    //add audio
    std::string soundNames = blueprint->get("Object.Audio.Sounds","");
    StrTokens tokens = tokenise(soundNames, ';');
    StrTokens::iterator iToken=tokens.begin();
    while(iToken!=tokens.end())
    {
        StrTokens splitToken = tokenise(*iToken, ' ');
        if (splitToken.size()==2)
        {
            std::string key = splitToken[0];
            std::string soundBufferName = splitToken[1];
            std::cout << "Attempting to add sound to object as " << key << " x " << soundBufferName << std::endl;
            sf::SoundBuffer* buffer = core_->getStore()->getSoundBuffer(soundBufferName);
            std::cout << "Sound buffer address: " << buffer << std::endl;
            sf::Sound sound;
            sound.SetBuffer(*buffer);
            sound.Play();
            audio->addSound(key, buffer);
//                audio->addSound(key, core_->getStore()->getSoundBuffer(soundBufferName));
        }

        ++iToken;
    }

    return true;
}


bool ObjectBuilder::addAiComp_(ObjectId objectId, Object* object, Blueprint* blueprint)
{
    object->addFlag(cFlag::Ai);
    core_->getAiSub()->addComponent(objectId);
    AiComp* ai = core_->getAiSub()->getComponent(objectId);

    return true;
}



bool ObjectBuilder::addEventComp_(ObjectId objectId, Object* object, Blueprint* blueprint)
{
    object->addFlag(cFlag::Event);
    core_->getEventSub()->addComponent(objectId);
    EventComp* event = core_->getEventSub()->getComponent(objectId);
    std::string eventStr = blueprint->get("Object.Events.Messages","");
    //split by /
    StrTokens events = tokenise(eventStr,'/');
    StrTokens::iterator iEvent = events.begin();
    while(iEvent!=events.end())
    {
        //split by =
        StrTokens scSplit = tokenise(*iEvent,'=');
        std::string key = scSplit[0];
        std::string msgs = scSplit[1];
        event->addEvents(key,msgs);
        ++iEvent;
    }

    return true;
}



bool ObjectBuilder::addNameComp_(ObjectId objectId, Object* object, Blueprint* blueprint)
{
    object->addFlag(cFlag::Name);
    core_->getNameSub()->addComponent(objectId);
    NameComp* name = core_->getNameSub()->getComponent(objectId);
    name->setName(blueprint->get("Object.Name","NO NAME"));

    return true;
}


bool ObjectBuilder::addCoordsComp_(ObjectId objectId, Object* object, Blueprint* blueprint)
{
    object->addFlag(cFlag::Coords);
    core_->getCoordsSub()->addComponent(objectId);
    CoordsComp* coords = core_->getCoordsSub()->getComponent(objectId);
    coords->setCoords(Vector2d(blueprint->get("Object.Coords.x",0.f) , blueprint->get("Object.Coords.y",0.f)));
    //if it has gfx, set dimensions too
    GfxComp* gfxComp = core_->getGfxSub()->getComponent(objectId);
    if (gfxComp)
    {
        const sf::Image* image =gfxComp->getSprite()->GetImage();

        coords->setDimensions(Vector2d(gfxComp->getSprite()->GetImage()->GetWidth(), gfxComp->getSprite()->GetImage()->GetWidth()));
        std::cout << "DIMS: " << coords->getDimensions() << std::endl;
    }

    return true;
}


bool ObjectBuilder::addHealthComp_(ObjectId objectId, Object* object, Blueprint* blueprint)
{
    object->addFlag(cFlag::Health);
    core_->getHealthSub()->addComponent(objectId);
    HealthComp* health = core_->getHealthSub()->getComponent(objectId);
    health->setMax(blueprint->get("Object.Health.Max", 0));
    health->setCurrent(blueprint->get("Object.Health.Current", 0));
    health->addOnZeroHealthMessages(blueprint->get("Object.Health.onZeroHealth",""));

    return true;
}


bool ObjectBuilder::addMoveComp_(ObjectId objectId, Object* object, Blueprint* blueprint)
{
    object->addFlag(cFlag::Move);
    core_->getMoveSub()->addComponent(objectId);
    MoveComp* move = core_->getMoveSub()->getComponent(objectId);
//        blueprint->find("Object.Move.x");
//        blueprint->insert(blueprint->find("Object.Move.x"),10.f)
//        blueprint->put("Object.Move.x","1");
    move->setMove(Vector2d(blueprint->get("Object.Move.x",0.f), blueprint->get("Object.Move.y",0.f)));

    return true;
}


bool ObjectBuilder::addLauncherComp_(ObjectId objectId, Object* object, Blueprint* blueprint)
{
    object->addFlag(cFlag::Launcher);
    core_->getLauncherSub()->addComponent(objectId);
    LauncherComp* launcher = core_->getLauncherSub()->getComponent(objectId);
    launcher->setMaxCooldown(blueprint->get("Object.Launcher.MaxCooldown",0.f));
    launcher->setProjectileBlueprintName(blueprint->get("Object.Launcher.Projectile",""));

    return true;
}


bool ObjectBuilder::addCollisionComp_(ObjectId objectId, Object* object, Blueprint* blueprint)
{
    object->addFlag(cFlag::Collision);
    core_->getCollisionSub()->addComponent(objectId);
    CollisionComp* collision = core_->getCollisionSub()->getComponent(objectId);
    collision->addOnCollisionMessages(blueprint->get("Object.Collision.onCollision",""));

    return true;
}


