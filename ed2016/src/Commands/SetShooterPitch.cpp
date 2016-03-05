#include <Commands/SetShooterPitch.h>
#include <Subsystems/Sensors.h>
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
	pid_mode = false;
}
/*
//PID constructor
SetShooterPitch::SetShooterPitch(ShooterPitchPID::AnglePresets angle, float error)
{
	Requires(&*shooter_pitch);

	pitch = angle;
	accepted_error = error;
	interrupted = false;
	pid_mode = false;
}
*/

// Called just before this Command runs the first time
void SetShooterPitch::Initialize()
{
	log->write(Log::TRACE_LEVEL, "SetShooterPitch (angle: %f, pid mode: %d)", pitch, pid_mode);
	interrupted = false;
	if (sensors->areShooterAngleEnabled())
	{
		SetTimeout(TIMEOUT * fabs(pitch - sensors->shooterAngle()));
	}
	else
	{
		if(pid_mode) {
			pid_mode = false;
			log->write(Log::WARNING_LEVEL, "Warning: Shooter angle is disabled. Disabling PID mode");
		}
		SetTimeout(TIMEOUT * fabs(pitch - last_angle));
	}
	/*
	if(pid_mode) {
		shooter_pitch_->SetSetpoint(pitch);
		shooter_pitch_pid->SetAbsoluteTolerance(accepted_error);
		shooter_pitch_pid->Enable();
	}
	else {
		shooter_pitch_pid->Disable();
	}*/
}

// Called repeatedly when this Command is scheduled to run
void SetShooterPitch::Execute()
{
	if(!pid_mode) {
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
			shooter_pitch->setShooterPitchDirection(Utils::VerticalDirection::UP);
		}
		else if (pitch < current_angle)
		{
			shooter_pitch->setShooterPitchDirection(Utils::VerticalDirection::DOWN);
		}
		else
		{
			shooter_pitch->setShooterPitchDirection(Utils::VerticalDirection::V_STILL);
		}
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
	/*if(pid_mode) {
		if(IsTimedOut() && !(current_angle > pitch - accepted_error && current_angle < pitch + accepted_error)) {
			Log::getInstance()->write(Log::WARNING_LEVEL, "SetShooterPitch timed out while in PID mode. Sensor may be broken or the loop"
					"may need tuning. (Target: %f, Current: %f)", pitch, current_angle);
			shooter_pitch_pid->Disable();
			return true;
		}
	}*/
	//else {
		if (current_angle > pitch - accepted_error && current_angle < pitch + accepted_error)
		{
			return true;
		}
		else if(IsTimedOut()) {
			Log::getInstance()->write(Log::WARNING_LEVEL, "SetShooterPitch timed out when trying to reach angle %f (Current Angle: %f)", pitch, current_angle);
			return true;
		}
	//}
	return false;
}

// Called once after isFinished returns true
void SetShooterPitch::End()
{

	shooter_pitch->setShooterPitchDirection(Utils::VerticalDirection::V_STILL);
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
	log->write(Log::TRACE_LEVEL,"SetShooterPitch Interrupted");
	interrupted = true;
	End();
}

void SetShooterPitch::zeroTimedAngleTracker()
{
	last_angle = 0.0;
}
