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
		AddSequential(new DriveDistance(259)); //Intentionally 2.5 feet over estimate
	}
	else if (def == PORTCULLIS)
	{
		AddSequential(new DriveDistance(150));	//rough estimate, probably needs to be fixed
		AddSequential(new AngleIntake(75.0));		//rough estimate, probably needs to be fixed
		AddParallel(new DriveDistance(122));	//rough estimate, probably needs to be fixed
		AddSequential(new AngleIntake(50.0));		//rough estimate, probably needs to be fixed
	}
	else if (def == DRAWBRIDGE)
	{
		AddSequential(new DriveDistance(274));	//rough estimate, probably needs to be fixed
		//figure out how to move the drawbridge arm later
	}
	else if (def == SALLY_PORT)
	{
		AddSequential(new DriveDistance(274));	//rough estimate, probably needs to be fixed
		//figure out how to move the drawbridge arm later
	}
	else if (def == CHEVAL_DE_FRISES)
	{
		AddSequential(new DriveDistance(150));
		AddSequential(new AngleIntake(50));		//blah blah rough blah blah estimate
		AddSequential(new DriveDistance(122));
	}
}
