#include "Systems.h"
#include "HealthComp.h"
#include <iostream>

template <>
void System<HealthComp>::update(double elapsed)
{
    std::cout << "Updating HealthComp" << std::endl;

    //update all health components
    std::map<ObjectId,HealthComp>::iterator iCom = components_.begin();
    while(iCom!=components_.end())
    {
        HealthComp* currComponent = &iCom->second;

        //ensure current health is in bound
        if(currComponent->getCurrent() > currComponent->getMax())
        {
            currComponent->setCurrent(currComponent->getMax());
        }

        if(currComponent->getCurrent() <= 0)
        {
            //send an onZeroHealth message
        }

        ++iCom;
    }

//    std::cout << "Updating Sub" << std::endl;
//    //read messages
//    std::vector<Message>::iterator iMessage = messages_.begin();
//    while(iMessage!=messages_.end())
//    {
//        deliverMessage_(*iMessage);
//        ++iMessage;
//    }
//    //clear messages
//    messages_.clear();
//
//    //render stuff
//    std::map<ObjectId,GfxComponent>::iterator iCom = components_.begin();
//
//    //grab ui
//    sf::RenderWindow* window_ = getCore()->getUi()->getWindow();
//
//    //render
//    std::cout << &window_ << std::endl;
//    std::cout << window_ << std::endl;
//    window_->Clear();
//    while(iCom!=components_.end())
//    {
//        std::cout << " ->" << iCom->second.getId() << std::endl;
//        //get sprite
//        sf::Sprite* sprite = iCom->second.getSprite();
//
//        //get coordsCom
//        CoordsComponent* coordsCom = core_->getCoordsSub()->getComponent(iCom->second.getId());
//
//        Vector2d coords = coordsCom->getCoords();
//        std::cout << "   -> @ " << coords.x << "," << coords.y << std::endl;
//        sprite->SetX(coords.x);
//        sprite->SetY(coords.y);
//        window_->Draw(*sprite);
//        ++iCom;
//    }
//    window_->Display();

}


template <>
void System<HealthComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to HealthComps" << std::endl;
    //check if target entity is registered with this subsystem
    HealthComp* targetComponent = getComponent(message.getSourceId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];

    if (mainCmd=="changeMaxBy")
    {
        targetComponent->setMax(targetComponent->getMax() + atoi(params[2].c_str()));
    }

    else if (mainCmd=="changeCurrBy")
    {
        targetComponent->setCurrent(targetComponent->getCurrent() + atoi(params[2].c_str()));
    }

    else if (mainCmd=="changeMaxTo")
    {
        targetComponent->setMax(atoi(params[2].c_str()));
    }

    else if (mainCmd=="changeCurrTo")
    {
        targetComponent->setCurrent(atoi(params[2].c_str()));
    }

    else if (mainCmd=="restoreToMax")
    {
        targetComponent->setCurrent(targetComponent->getMax());
    }

//    if(mainCmd=="change")
//    {
//        targetComponent->setSprite(params[2]);
//    }
}
