#include "LowerShooterToZero.h"
#include <Subsystems/ShooterPitch.h>
#include <RobotMap.h>
#include <Subsystems/Sensors.h>
LowerShooterToZero::LowerShooterToZero()
{
	Requires(&*shooter_pitch);
	was_pid_enabled = false;
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerShooterToZero::Initialize()
{
	log->write(Log::TRACE_LEVEL, "LowerShooterToZero Initialized");
	was_pid_enabled = shooter_pitch->isPIDEnabled();
	if (shooter_pitch->isPIDEnabled())
	{
		shooter_pitch->Disable();
	}

}

// Called repeatedly when this Command is scheduled to run
void LowerShooterToZero::Execute()
{
	if(sensors->isShooterHomeSwitchHorizontal() == false)
	{
	shooter_pitch->setDirection(Utils::VerticalDirection::DOWN);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool LowerShooterToZero::IsFinished()
{
	if(sensors->isShooterHomeSwitchHorizontal())
	{
		sensors->isShooterHomeSwitchHorizontal();
	}
	return sensors->isShooterHomeSwitchHorizontal();
}

// Called once after isFinished returns true
void LowerShooterToZero::End()
{
	log->write(Log::TRACE_LEVEL, "LowerShooterToZero Ended");
	if (was_pid_enabled && sensors->areShooterAngleEnabled())
	{
		shooter_pitch->Enable();
		shooter_pitch->SetSetpoint(sensors->shooterAngle());
	}
	shooter_pitch->setDirection(Utils::VerticalDirection::V_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerShooterToZero::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "LowerShooterToZero Interrupted");
}
