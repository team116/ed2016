#include "CrossDefense.h"
#include <Commands/Autonomous/MoveToDefense.h>
#include <Commands/DriveDistance.h>
#include <Commands/AngleIntake.h>
#include <Autonomous.h>

CrossDefense::CrossDefense(Autonomous::Defense def)
{
	AddSequential(new MoveToDefense());

	if (def == MOAT || def == RAMPARTS || def == ROCK_WALL || def == ROUGH_TERRAIN || def == LOW_BAR)
	{
		AddSequential(new DriveDistance(5.7));
	}
	else if (def == PORTCULLIS)
	{
		AddSequential(new DriveDistance(0.3));	//rough estimate, probably needs to be fixed
		AddSequential(new AngleIntake(75.0));		//rough estimate, probably needs to be fixed
		AddParallel(new DriveDistance(4.0));	//rough estimate, probably needs to be fixed
		AddSequential(new AngleIntake(50.0));		//rough estimate, probably needs to be fixed
	}
	else if (def == DRAWBRIDGE)
	{
		AddSequential(new DriveDistance(0.3));	//rough estimate, probably needs to be fixed
		//figure out how to move the drawbridge arm later
	}
	else if (def == SALLY_PORT)
	{
		AddSequential(new DriveDistance(0.3));	//rough estimate, probably needs to be fixed
		//figure out how to move the drawbridge arm later
	}
}
