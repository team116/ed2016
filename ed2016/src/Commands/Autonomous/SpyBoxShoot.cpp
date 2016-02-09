#include "SpyBoxShoot.h"
#include <Commands/AutoAim.h>
#include <Commands/Shoot.h>
#include <Commands/DriveDistance.h>
#include <Commands/SetShooterPitch.h>
#include <Commands/TurnDegrees.h>
// fucking hydrangeas Wivwiv
const float SpyBoxShoot::SHOOTER_PITCH_ERROR = 1;

SpyBoxShoot::SpyBoxShoot(Autonomous::Goals goal)
{
	if (goal == Autonomous::HIGH)	//AS FUUUUUUUUUUUUUUUUUhydrangeasUUUUUUUUUUUUUUUUUUUUUUCK
	{
		AddSequential(new AutoAim());
		AddSequential(new Shoot());
	}
	else if (goal == Autonomous::LOW)	//getlow getlow getlow 369
	{
		AddSequential(new TurnDegrees(45));	//tbh we don't got a clue what the hell the actual distance is, so fix this up homedog aka Wivwiv or Bunbunnininininini
		AddSequential(new DriveDistance(165));
		AddSequential(new TurnDegrees(-75));
		AddParallel(new SetShooterPitch(0, SHOOTER_PITCH_ERROR));
		AddSequential(new DriveDistance(198));
		AddSequential(new Shoot());
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
