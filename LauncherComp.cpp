#include "LauncherComp.h"

LauncherComp::LauncherComp(ObjectId id): Component(id, cType::Launcher)
{
    std::cout << "Creating LauncherComp" << std::endl;

    currCooldown_ = 0;
    onCooldown_ = false;
}


void LauncherComp::setAngle(double a)
{
    angle_ = a;
}


double LauncherComp::getAngle()
{
    return angle_;
}


void LauncherComp::setSpeed(double s)
{
    speed_ = s;
}


double LauncherComp::getSpeed()
{
    return speed_;
}



void LauncherComp::setMaxCooldown(double c)
{
    maxCooldown_ = c;
}


double LauncherComp::getMaxCooldown()
{
    return maxCooldown_;
}


void LauncherComp::reduceCooldownBy(double c)
{
    currCooldown_ -=c;
}


double LauncherComp::getCurrCooldown()
{
    return currCooldown_;
}


void LauncherComp::setOnCooldown(bool c)
{
    onCooldown_ = c;
}


void LauncherComp::setCurrCooldown(double c)
{
    currCooldown_ = c;
}


bool LauncherComp::isOnCooldown()
{
    return onCooldown_;
}


void LauncherComp::setProjectileBlueprintName(std::string bpName)
{
    projectileBlueprintName_ = bpName;
}


std::string LauncherComp::getProjectileBlueprintName()
{
    return projectileBlueprintName_;
}
