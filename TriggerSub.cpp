#include "Systems.h"
#include "Core.h"
#include "TriggerComp.h"
#include "Ui.h"
#include "Telegram.h"
#include "MessageCentre.h"
#include <iostream>


template <>
void System<TriggerComp>::update(double elapsed)
{

    std::map<ObjectId,TriggerComp>::iterator iCom = components_.begin();

//    //update position based on parent
//    while(iCom!=components_.end())
//    {
//        AnchorComp* anchorComp = &iCom->second;
//        //check if parent still exists! i.e., if parent has no coords, get rid of this comp
//        CoordsComp* parentCoordsComp = core_->getCoordsSub()->getComponent(anchorComp->getParentEntity());
//        if (parentCoordsComp==NULL) //TODO: Add switch to anchor comp so that it can br configured whether this entity dies when parent does
//        {
//            //register for desctruction
//            Parameters destructParams;
//            destructParams.push_back("object");
//            destructParams.push_back("destroy");
//            Message destructMsg(iCom->first, iCom->first, destructParams);
//            Telegram destructTelegram(iCom->first, iCom->first, 0.0, destructMsg);
//            core_->getMessageCentre()->addTelegram(destructTelegram);
//            ++iCom;
//            continue;
//        }
//
//
//        //get anchored objects coord comps and update them
//        CoordsComp* childCoordsComp = core_->getCoordsSub()->getComponent(iCom->first);
//        if (childCoordsComp != NULL)
//        {
//            childCoordsComp->setCoords(parentCoordsComp->getCenter()+anchorComp->getOffset() - (childCoordsComp->getDimensions()/2));
//        }
//
//        ++iCom;
//    }


}



template <>
void System<TriggerComp>::deliverMessage_(Message message)
{
    std::cout << "Delivering message to TriggerComps" << std::endl;
    //check if target entity is registered with this subsystem
    TriggerComp* targetComponent = getComponent(message.getTargetId());
    if(targetComponent==NULL)
    {
        return;
    }

    Parameters params = message.getParameters();

    //read message!
    std::string mainCmd = params[1];


    if (mainCmd=="activate")
    {
        std::string activationTag = params[2];




        //TODO: This is currently hard coded, but needn't be
        std::vector<ObjectId> ids = targetComponent->getTriggeredObjects(activationTag);
        std::vector<Parameters> trigParams = targetComponent->getTriggeredParameters(activationTag);
        std::cout << "There are " << ids.size() << " target objects for '" << activationTag << "' tag" << std::endl;
        std::vector<ObjectId>::iterator iId = ids.begin();
        while(iId!=ids.end())
        {
            std::cout << "Processing message for object "<< *iId << std::endl;
            //for each set of message params, send a message
            std::vector<Parameters>::iterator iParams = trigParams.begin();
            while(iParams != trigParams.end())
            {
                //bundle message and send it
                Message trigMsg(message.getTargetId(), *iId, *iParams);
                Telegram trigTelegram(message.getTargetId(), *iId,0.0, trigMsg);
                core_->getMessageCentre()->addTelegram(trigTelegram);
                ++iParams;
            }
            ++iId;
        }
    }

}


template <>
void System<TriggerComp>::init()
{

}
