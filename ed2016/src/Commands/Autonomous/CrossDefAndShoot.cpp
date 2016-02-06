#include <Commands/Autonomous/CrossDefAndShoot.h>
#include <Commands/Autonomous/CrossDefense.h>
#include <Autonomous.h>
#include <Commands/AutoAim.h>
#include <Commands/Shoot.h>
#include <Commands/DriveDistance.h>
#include <Commands/SweepForGoal.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Cameras.h>

CrossDefAndShoot::CrossDefAndShoot(Autonomous::Defense def, Autonomous::Goals goal, int initial_position)
{
	AddSequential(new CrossDefense(def));

	if (goal == Autonomous::HIGH)
		{
			float angle = sensors->robotAngle();
			AddSequential(new SweepForGoal(initial_position));
			AddSequential(new AutoAim());
			AddSequential(new Shoot());
		}

	else if (goal == Autonomous::LOW)
		{
			AddSequential(new DriveDistance(2.5)); //This is a stand-in value, we need to find out distance from low goal
			//either push or shoot
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
