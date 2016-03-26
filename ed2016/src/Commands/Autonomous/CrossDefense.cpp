#include "CrossDefense.h"
#include <Commands/Autonomous/MoveToDefense.h>
#include <Commands/SetShooterPitch.h>
#include <Commands/DriveDistance.h>
#include <Commands/DriveStraight.h>
#include <Commands/AngleIntake.h>
#include <Subsystems/Shooter.h>
#include <Autonomous.h>

CrossDefense::CrossDefense(Autonomous::Defense def)
{
	log = Log::getInstance();
	AddSequential(new AngleIntake(90.0));
	if (def == Autonomous::MOAT)
	{
		AddSequential(new SetShooterPitch(ShooterPitch::getAnglePreset(1)));
	}
	AddSequential(new DriveStraight(1.0, DriveStraight::SensorType::GYRO, 3.1)); //temporary time
}
