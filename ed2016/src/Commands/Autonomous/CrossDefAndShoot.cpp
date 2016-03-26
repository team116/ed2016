#include <Commands/Autonomous/CrossDefAndShoot.h>
#include <Commands/Autonomous/CrossDefense.h>
#include <Commands/Autonomous/MoveToDefense.h>
#include <Commands/Autonomous/TimedDoNothing.h>
#include <Autonomous.h>
#include <Commands/AutoShoot.h>
#include <Commands/Shoot.h>
#include <Commands/DriveDistance.h>
#include <Commands/SweepForGoal.h>
#include <Commands/TurnDegrees.h>
#include <Commands/AngleIntake.h>
#include <Commands/TurnToAngle.h>
#include <Commands/DriveByLidar.h>
#include <Commands/SetShooterWheels.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Cameras.h>
#include <Subsystems/Shooter.h>

CrossDefAndShoot::CrossDefAndShoot(Autonomous::Defense def, Autonomous::Goals goal, int initial_position)
{
	log = Log::getInstance();

	AddSequential(new CrossDefense(def));
	AddSequential(new TimedDoNothing(1.0));
	AddSequential(new AutoShoot());
}

/*void CrossDefAndShoot::Initialize()
{

}

void CrossDefAndShoot::Execute()
{

}

bool CrossDefAndShoot::IsFinished()
{
	return false;
}

void CrossDefAndShoot::End()
{

}

void CrossDefAndShoot::Interrupted()
{

}
*/
