#include <Commands/TurnToAngle.h>
#include <Subsystems/Mobility.h>
#include <Subsystems/Sensors.h>

const float TurnToAngle::TURN_SPEED = 0.75;

TurnToAngle::TurnToAngle(float target, float err)
{
	Requires(&*mobility);
	target_angle = target;
	angle = 0.0;
	error = err;
	interrupted = false;
}

// Called just before this Command runs the first time
void TurnToAngle::Initialize()
{
	log->write(Log::TRACE_LEVEL,"TurnToAngle Initialized (target, %f)", target_angle);
	interrupted = false;
}

// Called repeatedly when this Command is scheduled to run
void TurnToAngle::Execute()
{
	angle = sensors->robotAngle();
	if (angle > target_angle)
	{
		if (target_angle < angle-180)
		{
			mobility->setLeft(TURN_SPEED);
			mobility->setRight(-TURN_SPEED);
		}
		else
		{
			mobility->setLeft(-TURN_SPEED);
			mobility->setRight(TURN_SPEED);
		}
	}
	else
	{
		if (angle < target_angle-180)
		{
			mobility->setLeft(-TURN_SPEED);
			mobility->setRight(TURN_SPEED);
		}
		else
		{
			mobility->setLeft(TURN_SPEED);
			mobility->setRight(-TURN_SPEED);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool TurnToAngle::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	else if (angle > target_angle - error && angle < target_angle + error)
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void TurnToAngle::End()
{
	log->write(Log::TRACE_LEVEL,"TurnToAngle Ended");
	mobility->setStraight(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnToAngle::Interrupted()
{
	log->write(Log::TRACE_LEVEL,"TurnToAngle Interrupted");
	End();
	interrupted = true;
}
