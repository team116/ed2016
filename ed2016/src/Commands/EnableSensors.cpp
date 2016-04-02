#include <Commands/EnableSensors.h>
#include <Subsystems/Sensors.h>

EnableSensors::EnableSensors(bool enable)
{
	this->enable = enable;
}

// Called just before this Command runs the first time
void EnableSensors::Initialize()
{
	log->write(Log::TRACE_LEVEL, "EnableSensors initialized (enable: %d)", enable);

	sensors->enableDriveEncoders(enable);
	sensors->enableIntakeAngle(enable);
	sensors->enableLidar(enable);
	sensors->enableRobotAngle(enable);
	sensors->enableShooterAngle(enable);
	sensors->enableShooterHomeSwitch(enable);
	sensors->enableShooterWheelTachometer(enable);
}

// Called repeatedly when this Command is scheduled to run
void EnableSensors::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool EnableSensors::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void EnableSensors::End()
{
	log->write(Log::TRACE_LEVEL, "EnableSensors ended");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void EnableSensors::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "EnableSensors interrupted");
	End();
}
