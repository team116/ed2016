#include "MoveToDefense.h"
#include <Commands/AngleIntake.h>
#include <Commands/DriveDistance.h>
#include <RobotMap.h>
#include <Log.h>

MoveToDefense::MoveToDefense()
{
	log = Log::getInstance();
	log->write(Log::TRACE_LEVEL, "Moving to Defense");
	AddSequential(new AngleIntake(90.0));
	AddSequential(new DriveDistance(152.0)); //temporary time
}
