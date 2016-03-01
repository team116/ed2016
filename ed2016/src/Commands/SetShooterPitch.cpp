#include <Commands/SetShooterPitch.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/ShooterPitch.h>
#include <Log.h>

const float SetShooterPitch::DEFAULT_ACCEPTABLE_ERROR = 1.0;
const float SetShooterPitch::TIMEOUT = 0.025;
float SetShooterPitch::last_angle = 0.0;

//Angle in degrees
SetShooterPitch::SetShooterPitch(float angle, float error)
{
	// Use Requires(&*) here to declare subsystem dependencies
	Requires(&*shooter_pitch);

	pitch = angle;
	accepted_error = error;
	interrupted = false;
}

// Called just before this Command runs the first time
void SetShooterPitch::Initialize()
{
	log->write(Log::TRACE_LEVEL, "SetShooterPitch (angle %f)", pitch);
	interrupted = false;
	if (sensors->areShooterAngleEnabled())
	{
		SetTimeout(TIMEOUT * fabs(pitch - sensors->shooterAngle()));
	}
	else
	{
		SetTimeout(TIMEOUT * fabs(pitch - last_angle));
	}
}

// Called repeatedly when this Command is scheduled to run
void SetShooterPitch::Execute()
{
	float current_angle;
	if (sensors->areShooterAngleEnabled())
	{
		current_angle = sensors->shooterAngle();
	}
	else
	{
		current_angle = last_angle;
	}

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
	float current_angle;
	if (sensors->areShooterAngleEnabled())
	{
		current_angle = sensors->shooterAngle();
	}
	else
	{
		current_angle = last_angle;
	}

	if (interrupted)
	{
		return true;
	}
	else if (current_angle > pitch - accepted_error && current_angle < pitch + accepted_error)
	{
		return true;
	}
	else if(IsTimedOut()) {
		Log::getInstance()->write(Log::WARNING_LEVEL, "SetShooterPitch timed out when trying to reach angle %f (Current Angle: %f)", pitch, current_angle);
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void SetShooterPitch::End()
{
	shooter_pitch->setShooterPitchDirection(ShooterPitch::SHOOTER_STILL);
	last_angle = pitch;

	float angle;
	if (sensors->areShooterAngleEnabled())
	{
		angle = sensors->shooterAngle();
	}
	else
	{
		angle = last_angle;
	}
	log->write(Log::TRACE_LEVEL,"SetShooterPitch Ended (angle %f)", angle);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShooterPitch::Interrupted()
{
	log->write(Log::TRACE_LEVEL,"SeShooterPitch Interrupted");
	interrupted = true;
	End();
}

void SetShooterPitch::zeroTimedAngleTracker()
{
	last_angle = 0.0;
}
