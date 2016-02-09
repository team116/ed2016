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
	AddSequential(new SpyBoxShoot(goal));

	if(goal == Autonomous::HIGH)
	{
		AddSequential(new TurnDegrees(-15));//Inaccurate value
		AddSequential(new DriveDistance(180));//Inaccurate value
	}
	else
	{
		AddSequential(new DoNothing());
	}
}
SpyBoxShootAndReach::~SpyBoxShootAndReach() {
	// TODO Auto-generated destructor stub
}


void SpyBoxShootAndReach::Initialize()
{

}

void SpyBoxShootAndReach::Execute()
{

}

bool SpyBoxShootAndReach::IsFinished()
{
	return false;
}

void SpyBoxShootAndReach::End()
{

}

void SpyBoxShootAndReach::Interrupted()
{

}
