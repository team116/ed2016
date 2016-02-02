#ifndef CrossDefense_H
#define CrossDefense_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

class CrossDefense: public CommandGroup
{
public:
	enum Defenses {
		PORTCULLIS,
		CHEVAL_DE_FRISE,
		MOAT,
		RAMPARTS,
		DRAWBRIDGE,
		SALLY_PORT,
		ROCK_WALL,
		ROUGH_TERRAIN,
		LOW_BAR
	};
	CrossDefense(Defenses);
};

#endif
