#include "AutoShoot.h"
#include <Commands/AngleIntake.h>
#include <Commands/Shoot.h>
#include <Commands/TurnToTarget.h>
#include <Commands/AimShooterToTarget.h>
#include <Commands/SetShooterWheels.h>
#include <Commands/SetShooterPitch.h>
#include <Subsystems/Shooter.h>

AutoShoot::AutoShoot()
{
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

	AddParallel(new SetShooterPitch(30.0));
	AddParallel(new SetShooterWheels(CommandBase::shooter->getRPMPreset(5)));
	AddSequential(new TurnToTarget());
	AddSequential(new AngleIntake(0.0));
	AddSequential(new AimShooterToTarget());
	AddSequential(new Shoot());
}
