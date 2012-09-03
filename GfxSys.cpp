#include "Systems.h"
#include "GfxComp.h"
#include "CoordsComp.h"
#include "Core.h"
#include "Ui.h"
#include <iostream>

template <>
void System<GfxComp>::update(double elapsed)
{
//    std::cout << "Updating GfxComps" << std::endl;

    //update all gfx components
//    std::map<ObjectId,GfxComp>::iterator iCom = components_.begin();
//    while(iCom!=components_.end())
//    {
//        GfxComp* currComp = &iCom->second;
//
//        ++iCom;
//    }



    //render stuff
    std::map<ObjectId,GfxComp>::iterator iCom = components_.begin();

    //grab ui
    sf::RenderWindow* window_ = getCore()->getUi()->getWindow();

    //render

    window_->Clear();
    while(iCom!=components_.end())
    {
//        std::cout << " ->" << iCom->second.getId() << std::endl;
        //get sprite
        sf::Sprite* sprite = iCom->second.getSprite();

        //get coordsCom
        CoordsComp* coordsCom = core_->getCoordsSub()->getComponent(iCom->second.getId());

        Vector2d coords = coordsCom->getCoords();
//        std::cout << "   -> @ " << coords.x << "," << coords.y << std::endl;
        sprite->SetX(coords.x);
        sprite->SetY(coords.y);
        window_->Draw(*sprite);
        ++iCom;
    }
    window_->Display();



}


template <>
void System<GfxComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to GfxComps" << std::endl;
    //check if target entity is registered with this subsystem
    GfxComp* targetComponent = getComponent(message.getSourceId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];

    if (mainCmd=="changeSprite")
    {
        targetComponent->setSprite(core_->getStore()->getImage(params[2]));
//        targetComponent->setLocalDestination(Vector2d(atoi(params[2].c_str()),atoi(params[3].c_str())));
    }
//
//    else if (mainCmd=="changeCurrBy")
//    {
//        targetComponent->setCurrent(targetComponent->getCurrent() + atoi(params[2].c_str()));
//    }


}
