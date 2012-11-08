#include "Goal.h"
#include "Vector2d.h"
#include "Core.h"
#include "Telegram.h"
#include "MessageCentre.h"
Goal::Goal(ObjectId sourceId, ObjectId targetId, Parameters params) : Message(sourceId,targetId, params)
{

};






bool GoalApproach::met()
{
    //get coords of source and target
    //TODO: for met and act, DO NOT DO IT LIKE THIS! Will break if target or source is now null! Get comp* first then try for vector2d if not null
    Vector2d sourceCo = getCore()->getCoordsSub()->getComponent(getSourceId())->getCoords();
    Vector2d targetCo = getCore()->getCoordsSub()->getComponent(getTargetId())->getCoords();

    if (sourceCo.getDistance(targetCo) <= minDistToTarget_)
    {
        return true;
    }

    return false;
}


void GoalApproach::act()
{
    //send message to move towards target
    //get coordinates
    Vector2d targetCo = getCore()->getCoordsSub()->getComponent(getTargetId())->getCoords();


        //set movement
        Parameters moveParameters;
        moveParameters.push_back("move");
        moveParameters.push_back("setLocalDest");
        std::stringstream xSS(""), ySS("");
        xSS << targetCo.x;
        ySS << targetCo.y;
        moveParameters.push_back(xSS.str());
        moveParameters.push_back(ySS.str());

    //send telegram
    Message message(getSourceId() , getTargetId(), moveParameters);
    Telegram telegram(getTargetId(), getTargetId(), 0.0, message);
    getCore()->getMessageCentre()->addTelegram(telegram);
}
