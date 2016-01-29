#include <SetShooterPitch.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/Sensors.h>


SetShooterPitch::SetShooterPitch(float angle)
{
	Requires(shooter);
	pitch = angle;

}

// Called just before this Command runs the first time
void SetShooterPitch::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void SetShooterPitch::Execute()
{
	float curent_angle = shooter->
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
