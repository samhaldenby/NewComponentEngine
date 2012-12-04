#include "Systems.h"
#include "Core.h"
#include "AnchorComp.h"
#include "Ui.h"
#include "Telegram.h"
#include "MessageCentre.h"
#include <iostream>


template <>
void System<AnchorComp>::update(double elapsed)
{

    std::map<ObjectId,AnchorComp>::iterator iCom = components_.begin();

    //update position based on parent
    while(iCom!=components_.end())
    {
        AnchorComp* anchorComp = &iCom->second;
        //check if parent still exists! i.e., if parent has no coords, get rid of this comp
        CoordsComp* parentCoordsComp = core_->getCoordsSub()->getComponent(anchorComp->getParentEntity());
        if (parentCoordsComp==NULL) //TODO: Add switch to anchor comp so that it can br configured whether this entity dies when parent does
        {
            //register for desctruction
            Parameters destructParams;
            destructParams.push_back("object");
            destructParams.push_back("destroy");
            Message destructMsg(iCom->first, iCom->first, destructParams);
            Telegram destructTelegram(iCom->first, iCom->first, 0.0, destructMsg);
            core_->getMessageCentre()->addTelegram(destructTelegram);
            ++iCom;
            continue;
        }


        //get anchored objects coord comps and update them
        CoordsComp* childCoordsComp = core_->getCoordsSub()->getComponent(iCom->first);
        if (childCoordsComp != NULL)
        {
            childCoordsComp->setCoords(parentCoordsComp->getCoords()+anchorComp->getOffset());
        }

        ++iCom;
    }


}



template <>
void System<AnchorComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to AnchorComps" << std::endl;
    //check if target entity is registered with this subsystem
    AnchorComp* targetComponent = getComponent(message.getTargetId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];



//    if (mainCmd=="changeSprite")
//    {
//        targetComponent->setSprite(core_->getStore()->getImage(params[2]));
////        targetComponent->setLocalDestination(Vector2d(atoi(params[2].c_str()),atoi(params[3].c_str())));
//    }
//
//    else if (mainCmd=="changeCurrBy")
//    {
//        targetComponent->setCurrent(targetComponent->getCurrent() + atoi(params[2].c_str()));
//    }


}


template <>
void System<AnchorComp>::init()
{

}
