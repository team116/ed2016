#include <Commands/ResetShooterAngle.h>
#include <Subsystems/Sensors.h>
#include <Log.h>

ResetShooterAngle::ResetShooterAngle()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void ResetShooterAngle::Initialize()
{
	log->write(Log::TRACE_LEVEL, "ResetShooterAngle Initialized");
	sensors->zeroShooterPitch();
}

// Called repeatedly when this Command is scheduled to run
void ResetShooterAngle::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ResetShooterAngle::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ResetShooterAngle::End()
{
	log->write(Log::TRACE_LEVEL, "ResetShooterAngle Ended");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetShooterAngle::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "ResetShooterAngle Interrupted");
}
