#ifndef SpyBoxShoot_H
#define SpyBoxShoot_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include <Autonomous.h>
#include <Log.h>

class SpyBoxShoot: public CommandGroup
{
public:
	SpyBoxShoot(Autonomous::Goals);
private:
	static const float SHOOTER_PITCH_ERROR;
	bool using_autoaim;
	Log* log;
};

#endif
