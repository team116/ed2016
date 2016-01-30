#include <Commands/SetShooterPitch.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Shooter.h>

SetShooterPitch::SetShooterPitch(float angle)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(shooter);

	pitch = angle;
}

// Called just before this Command runs the first time
void SetShooterPitch::Initialize()
{
	float curent_angle = sensors->shooterAngle();
}

// Called repeatedly when this Command is scheduled to run
void SetShooterPitch::Execute()
{

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
