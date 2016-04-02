#ifndef ManualOverride_H
#define ManualOverride_H

#include <Commands/CommandGroup.h>
#include "WPILib.h"

class ManualOverride: public CommandGroup
{
public:
	ManualOverride(bool override);
};

#endif
