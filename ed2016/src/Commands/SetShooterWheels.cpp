#include "SetShooterWheels.h"
#include <Subsystems/Shooter.h>

SetShooterWheels::SetShooterWheels(float rpm)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(&*shooter);

	SetTimeout(4.0);

	setpoint = rpm;
}

// Called just before this Command runs the first time
void SetShooterWheels::Initialize()
{
	log->write(Log::TRACE_LEVEL, "SetShooterWheels Initialize (setpoint: %f)", setpoint);
	shooter->setRPM(setpoint);
}

// Called repeatedly when this Command is scheduled to run
void SetShooterWheels::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterWheels::IsFinished()
{
	if(shooter->OnTarget()) {
		log->write(Log::TRACE_LEVEL, "ShooterWheels finished");
		return true;
	}
	else if (IsTimedOut())
	{
		log->write(Log::TRACE_LEVEL, "SetShooterWheels timed out");
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void SetShooterWheels::End()
{
	log->write(Log::TRACE_LEVEL, "SetShooterWheels Ended (setpoint: %f ontarget: %d)", setpoint, shooter->OnTarget());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShooterWheels::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "SetShooterWheels Interrupted (setpoint: %f ontarget: %d)", setpoint, shooter->OnTarget());
}
