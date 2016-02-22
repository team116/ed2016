#include "CheckLidar.h"
#include <Subsystems/Sensors.h>

CheckLidar::CheckLidar()
{
	Requires(&*sensors);
	distance = 0.0;
	lidar_read = false;
}

// Called just before this Command runs the first time
void CheckLidar::Initialize()
{
	log->write(Log::TRACE_LEVEL, "Check Lidar Initialized");

}

// Called repeatedly when this Command is scheduled to run
void CheckLidar::Execute()
{
	sensors->refreshLidar();
	distance = sensors->lidarDistance();
	lidar_read = true;
}

// Make this return true when this Command no longer needs to run execute()
bool CheckLidar::IsFinished()
{
	if(lidar_read)
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void CheckLidar::End()
{
	log->write(Log::TRACE_LEVEL, "Check Lidar Ended");

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CheckLidar::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "Check Lidar Interrupted");

}
