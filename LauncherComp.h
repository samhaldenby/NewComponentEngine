#ifndef LAUNCHERCOMP_H_INCLUDED
#define LAUNCHERCOMP_H_INCLUDED

#include "Components.h"

class LauncherComp : public Component
{
    private:
        double angle_;
        double speed_;
        double maxCooldown_;
        double currCooldown_;
        bool onCooldown_;
        std::string projectileBlueprintName_;
    public:

        LauncherComp(ObjectId id);
        void setAngle(double a);
        double getAngle();
        void setSpeed(double s);
        double getSpeed();
        void setMaxCooldown(double c);
        double getMaxCooldown();
        void reduceCooldownBy(double c);
        double getCurrCooldown();
        void setCurrCooldown(double c);
        void setOnCooldown(bool c);
        bool isOnCooldown();
        void setProjectileBlueprintName(std::string bpName);
        std::string getProjectileBlueprintName();
};

#endif // LAUNCHERCOMP_H_INCLUDED
