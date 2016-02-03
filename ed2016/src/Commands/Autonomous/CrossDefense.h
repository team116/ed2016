#ifndef CrossDefense_H
#define CrossDefense_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "Autonomous.h"
using namespace Autonomous;

class CrossDefense: public CommandGroup
{
public:

	CrossDefense(Defense);
};

#endif
