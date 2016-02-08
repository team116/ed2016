#include <Commands/Autonomous/CrossDefAndShoot.h>
#include <Commands/Autonomous/CrossDefense.h>
#include <Autonomous.h>
#include <Commands/AutoAim.h>
#include <Commands/Shoot.h>
#include <Commands/DriveDistance.h>
#include <Commands/SweepForGoal.h>
#include <Commands/TurnDegrees.h>
#include <Commands/AngleIntake.h>
#include <Commands/TurnToAngle.h>
#include <Commands/DriveByLidar.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Cameras.h>

CrossDefAndShoot::CrossDefAndShoot(Autonomous::Defense def, Autonomous::Goals goal, int initial_position)
{
	AddSequential(new CrossDefense(def));

	if (goal == Autonomous::HIGH)
		{
			AddSequential(new SweepForGoal(initial_position));
			AddSequential(new AutoAim());
			AddSequential(new Shoot());
		}

	else if (goal == Autonomous::LOW)
		{
			AddParallel(new AngleIntake(0.0));
			if (initial_position == 1)
			{
				AddSequential(new TurnToAngle(0.0));
				AddSequential(new DriveByLidar(53));
				AddSequential(new TurnToAngle(84.9));
				AddSequential(new DriveDistance(342));
				AddSequential(new Shoot());
			}
			else if (initial_position == 2)
			{
				AddSequential(new TurnToAngle(0.0));
				AddSequential(new DriveByLidar(53));
				AddSequential(new TurnToAngle(81));
				AddSequential(new DriveDistance(171));
				AddSequential(new Shoot());
			}
			else if (initial_position == 3)
			{
				AddSequential(new TurnToAngle(11.4));
				AddSequential(new DriveByLidar(61));
				AddSequential(new Shoot());
			}
			else if (initial_position == 4)
			{
				AddSequential(new TurnToAngle(5.2));
				AddSequential(new DriveByLidar(61));
				AddSequential(new Shoot());
			}
			else if (initial_position == 5)
			{
				AddSequential(new TurnToAngle(0.0));
				AddSequential(new DriveByLidar(53));
				AddSequential(new TurnToAngle(282));
				AddSequential(new DriveDistance(123));
				AddSequential(new Shoot());
				//TODO: FINISH ME
			}
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
