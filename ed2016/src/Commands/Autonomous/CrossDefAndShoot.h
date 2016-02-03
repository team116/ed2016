#ifndef CrossDefAndShoot_H
#define CrossDefAndShoot_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "Commands/Autonomous/CrossDefense.h"
#include "Autonomous.h"

class CrossDefAndShoot: public CommandGroup
{
public:

	CrossDefAndShoot(Autonomous::Defense, Autonomous::Goals);
};

#endif
