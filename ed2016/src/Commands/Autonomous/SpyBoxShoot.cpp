#include "SpyBoxShoot.h"
#include <Commands/AutoShoot.h>
#include <Commands/Shoot.h>
#include <Commands/DriveDistance.h>
#include <Commands/SetShooterPitch.h>
#include <Commands/TurnDegrees.h>
#include <Commands/SetShooterPitch.h>
#include <Commands/SetShooterWheels.h>
#include <Subsystems/Shooter.h>
// fucking hydrangeas

SpyBoxShoot::SpyBoxShoot(Autonomous::Goals goal)
{	log = Log::getInstance();
	using_autoaim = false;

	if (goal == Autonomous::HIGH)	//AS FUUUUUUUUUUUUUUUUUhydrangeasUUUUUUUUUUUUUUUUUUUUUUCK
	{
		log->write(Log::TRACE_LEVEL, "Shooting HIGH from Spy Box");
		if(using_autoaim)
			AddSequential(new AutoShoot());
		else {
			AddParallel(new SetShooterPitch(CommandBase::shooter_pitch->getPitchToTarget(349.61, 10)));
			AddSequential(new SetShooterWheels(CommandBase::shooter->getRPMPreset(5)));
			AddSequential(new Shoot());
		}
	}
	else if (goal == Autonomous::LOW)	//getlow getlow getlow 369
	{
		log->write(Log::TRACE_LEVEL, "Shooting LOW from Spy Box");
		AddSequential(new TurnDegrees(10));	//tbh we don't got a clue what the hell the actual distance is, so fix this up homedog aka Wivwiv or Bunbunnininininini
		AddSequential(new DriveDistance(10));
		AddSequential(new TurnDegrees(-10));
		AddParallel(new SetShooterPitch(0));
		AddSequential(new DriveDistance(250));
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
