#include <Commands/SetShooterPitch.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Shooter.h>

SetShooterPitch::SetShooterPitch(float angle)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(shooter);

	pitch = angle;
	interrupted = false;
}

// Called just before this Command runs the first time
void SetShooterPitch::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void SetShooterPitch::Execute()
{
	float current_angle = sensors->shooterAngle();
	if (pitch > current_angle)
	{
		shooter->setShooterPitchDirection(Shooter::SHOOTER_UP);
	}
	else if (pitch < current_angle)
	{
		shooter->setShooterPitchDirection(Shooter::SHOOTER_DOWN);
	}
	else
	{
		shooter->setShooterPitchDirection(Shooter::SHOOTER_STILL);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterPitch::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void SetShooterPitch::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShooterPitch::Interrupted()
{

}
