#include <Commands/SetShooterPitch.h>
#include <Commands/UpdateSensors.h>
#include <Subsystems/Sensors.h>

UpdateSensors::UpdateSensors()
{
	Requires(&*sensors);
	distance = 0.0;
	lidar_read = false;
}

// Called just before this Command runs the first time
void UpdateSensors::Initialize()
{
	log->write(Log::TRACE_LEVEL, "Update Sensors Initialized");
}
// Called repeatedly when this Command is scheduled to run
void UpdateSensors::Execute()
{
	sensors->updateTachometers();
	sensors->refreshLidar();

	if (sensors->isShooterHomeSwitchHorizontal())
	{
		sensors->zeroShooterPitch();
		SetShooterPitch::zeroTimedAngleTracker();
	}

	// this always needs to come last
	// other update functions might require cycle time
	// and the longer we do measurements, the less eratic our sensor values will be
	sensors->updateCycleTime();
}

// Make this return true when this Command no longer needs to run execute()
bool UpdateSensors::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void UpdateSensors::End()
{
	log->write(Log::TRACE_LEVEL, "Update Sensors Ended");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UpdateSensors::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "Update Sensors Interrupted");
}
