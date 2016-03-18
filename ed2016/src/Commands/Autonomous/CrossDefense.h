#ifndef CrossDefense_H
#define CrossDefense_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "Autonomous.h"
#include <Log.h>
using namespace Autonomous;

class CrossDefense: public CommandGroup
{
public:
	CrossDefense(Defense);
private:
	Log* log;
};

#endif
