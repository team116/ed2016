#include "MoveToDefense.h"
#include <Commands/AngleIntake.h>
#include <Commands/DriveStraight.h>
#include <RobotMap.h>
#include <Log.h>

MoveToDefense::MoveToDefense()
{
	log = Log::getInstance();
	log->write(Log::TRACE_LEVEL, "Moving to Defense");
	AddSequential(new AngleIntake(90.0));
	AddSequential(new DriveStraight(1.0, DriveStraight::SensorType::GYRO, 3.1)); //temporary time
}
