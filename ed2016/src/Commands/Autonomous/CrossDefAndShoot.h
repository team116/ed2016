#ifndef CrossDefAndShoot_H
#define CrossDefAndShoot_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "Commands/Autonomous/CrossDefense.h"

class CrossDefAndShoot: public CommandGroup
{
public:
	enum Goals {
		HIGH,
		LOW
	};
	CrossDefAndShoot(CrossDefense::Defenses, Goals);
};

#endif
