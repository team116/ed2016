#include "CrossDefense.h"
#include <Commands/Autonomous/MoveToDefense.h>
#include <Commands/DriveDistance.h>
#include <Commands/AngleIntake.h>
#include <Autonomous.h>

CrossDefense::CrossDefense(Autonomous::Defense def)
{
	AddSequential(new MoveToDefense());

	if (def == MOAT || def == RAMPARTS || def == ROUGH_TERRAIN )
	{
		AddSequential(new DriveDistance(259)); //Intentionally 2.5 feet over estimate
	}
	else if (def == PORTCULLIS)
	{
		AddSequential(new DriveDistance(9));	//rough estimate, probably needs to be fixed
		AddSequential(new AngleIntake(75.0));		//rough estimate, probably needs to be fixed
		AddParallel(new DriveDistance(122));	//rough estimate, probably needs to be fixed
		AddSequential(new AngleIntake(50.0));		//rough estimate, probably needs to be fixed
	}
	else if (def == DRAWBRIDGE)
	{
		AddSequential(new DriveDistance(9));	//rough estimate, probably needs to be fixed
		//figure out how to move the drawbridge arm later
	}
	else if (def == SALLY_PORT)
	{
		AddSequential(new DriveDistance(9));	//rough estimate, probably needs to be fixed
		//figure out how to move the drawbridge arm later
	}
}
