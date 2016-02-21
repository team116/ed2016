#include <Commands/SetShooterPitch.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/ShooterPitch.h>

//Angle in degrees
SetShooterPitch::SetShooterPitch(float angle, float error)
{
	// Use Requires(&*) here to declare subsystem dependencies
	Requires(&*shooter_pitch);
	SetTimeout(3.0);

	pitch = angle;
	accepted_error = error;
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
		shooter_pitch->setShooterPitchDirection(ShooterPitch::SHOOTER_UP);
	}
	else if (pitch < current_angle)
	{
		shooter_pitch->setShooterPitchDirection(ShooterPitch::SHOOTER_DOWN);
	}
	else
	{
		shooter_pitch->setShooterPitchDirection(ShooterPitch::SHOOTER_STILL);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterPitch::IsFinished()
{
	float current_angle = sensors->shooterAngle();

	if (interrupted)
	{
		return true;
	}
	else if (current_angle > pitch - accepted_error && current_angle < pitch + accepted_error)
	{
		return true;
	}
	else if(IsTimedOut()) {
		DriverStation::ReportError("SetShooterPitch timed out when trying to reach angle " + std::to_string(pitch) + " (Current Angle: " + std::to_string(current_angle) + ")");
	}
	return false;
}

// Called once after isFinished returns true
void SetShooterPitch::End()
{
	shooter_pitch->setShooterPitchDirection(ShooterPitch::SHOOTER_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShooterPitch::Interrupted()
{
	interrupted = true;
	End();
}
