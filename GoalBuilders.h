#ifndef GOALBUILDERS_H_INCLUDED
#define GOALBUILDERS_H_INCLUDED

#include "TypeDefs.h"

class Goal;

Goal* makeMoveGoal(Parameters args);
Goal* makeWaitGoal(Parameters args);

#endif // GOALBUILDERS_H_INCLUDED
