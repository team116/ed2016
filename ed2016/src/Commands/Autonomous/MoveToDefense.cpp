#include "MoveToDefense.h"
#include <Commands/DriveDistance.h>
#include <RobotMap.h>
#include <Log.h>

MoveToDefense::MoveToDefense()
{
	log = Log::getInstance();
	log->write(Log::TRACE_LEVEL, "Moving to Defense");
	AddSequential(new DriveDistance(152.0)); //temporary time
}
