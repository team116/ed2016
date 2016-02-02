#include "CrossDefense.h"
#include <Commands\DriveDistance.h>
#include <Commands\AngleIntake.h>

CrossDefense::CrossDefense(Defenses def)
{

	if (def == MOAT || def == RAMPARTS || def == ROCK_WALL || def == ROUGH_TERRAIN || def == LOW_BAR)
	{
		AddSequential(new DriveDistance(12));
	}
	else if (def == PORTCULLIS)
	{
		AddSequential(new DriveDistance(7));	//rough estimate, probably needs to be fixed
		AddSequential(new AngleIntake(75));		//rough estimate, probably needs to be fixed
		AddParallel(new DriveDistance(4));	//rough estimate, probably needs to be fixed
		AddSequential(new AngleIntake(50));		//rough estimate, probably needs to be fixed
	}
	else if (def = DRAWBRIDGE)
	{
		AddSequential(new DriveDistance(7));	//rough estimate, probably needs to be fixed
		//figure out how to move the drawbridge arm later
	}
	else if (def = SALLY_PORT)
		{
			AddSequential(new DriveDistance(7));	//rough estimate, probably needs to be fixed
			//figure out how to move the drawbridge arm later
		}
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}
