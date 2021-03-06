#include <Commands/SetShooterPitch.h>
#include <Subsystems/Sensors.h>
#include <Log.h>

const float SetShooterPitch::DEFAULT_ACCEPTABLE_ERROR = 2.0;
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
	log->write(Log::TRACE_LEVEL, "SetShooterPitch (angle: %f, pid mode: %d)", pitch, shooter_pitch->isPIDEnabled());
	interrupted = false;
	if (sensors->isShooterAngleEnabled())
	{
		SetTimeout(TIMEOUT * fabs(pitch - sensors->shooterAngle()));
	}
	else
	{
		if(shooter_pitch->isPIDEnabled()) {
			shooter_pitch->Disable();
			log->write(Log::WARNING_LEVEL, "Warning: Shooter angle is disabled. Disabling PID mode");
		}
		SetTimeout(TIMEOUT * fabs(pitch - last_angle));
	}

	if(shooter_pitch->isPIDEnabled()) {
		shooter_pitch->setAngle(pitch);
		//shooter_pitch->SetAbsoluteTolerance(accepted_error);
	}
}

// Called repeatedly when this Command is scheduled to run
void SetShooterPitch::Execute()
{
	if(!shooter_pitch->isPIDEnabled()) {
		float current_angle;
		if (sensors->isShooterAngleEnabled())
		{
			current_angle = sensors->shooterAngle();
		}
		else
		{
			current_angle = last_angle;
		}

		if (pitch > current_angle)
		{
			shooter_pitch->setDirection(Utils::VerticalDirection::UP);
		}
		else if (pitch < current_angle)
		{
			shooter_pitch->setDirection(Utils::VerticalDirection::DOWN);
		}
		else
		{
			shooter_pitch->setDirection(Utils::VerticalDirection::V_STILL);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterPitch::IsFinished()
{
	float current_angle;
	if (sensors->isShooterAngleEnabled())
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

	if (current_angle > pitch - accepted_error && current_angle < pitch + accepted_error)
	{
		return true;
	}
	else if(IsTimedOut())
	{
		Log::getInstance()->write(Log::WARNING_LEVEL, "SetShooterPitch timed out when trying to reach angle %f (Current Angle: %f)", pitch, current_angle);
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void SetShooterPitch::End()
{

	shooter_pitch->setDirection(Utils::VerticalDirection::V_STILL);
	last_angle = pitch;

	float angle;
	if (sensors->isShooterAngleEnabled())
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
	log->write(Log::TRACE_LEVEL,"SetShooterPitch Interrupted");
	interrupted = true;
	End();
}

void SetShooterPitch::zeroTimedAngleTracker()
{
	last_angle = 0.0;
}
