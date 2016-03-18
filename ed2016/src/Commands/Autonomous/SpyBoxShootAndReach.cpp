/*
 * SpyBoxShootAndReach.cpp
 *
 *  Created on: Jan 27, 2016
 *      Author: strahans
 */

#include <Commands/Autonomous/SpyBoxShootAndReach.h>
#include <Commands/Autonomous/SpyBoxShoot.h>
#include <Commands/TurnDegrees.h>
#include <Commands/DriveDistance.h>
#include <Commands/Autonomous/DoNothing.h>

SpyBoxShootAndReach::SpyBoxShootAndReach(Autonomous::Goals goal)
{
	log = Log::getInstance();
	AddSequential(new SpyBoxShoot(goal));

	if(goal == Autonomous::HIGH)
	{
		log->write(Log::TRACE_LEVEL, "Scaling the tower");
		AddSequential(new TurnDegrees(-15));//Inaccurate value
		AddSequential(new DriveDistance(180));//Inaccurate value
	}
	else
	{
		AddSequential(new DoNothing());
	}
}
