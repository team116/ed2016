#include <Commands/CheckLidar.h>
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
	sensors->updateTachometers();
	sensors->refreshLidar();

	// this always needs to come last
	// other update functions might require cycle time
	// and the longer we do measurements, the less eratic our sensor values will be
	sensors->updateCycleTime();
}

// Make this return true when this Command no longer needs to run execute()
bool CheckLidar::IsFinished()
{
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
