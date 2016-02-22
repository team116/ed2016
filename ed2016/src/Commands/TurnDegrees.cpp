#include <cmath>
#include <Commands/TurnDegrees.h>
#include <Subsystems/Mobility.h>
#include <Subsystems/Sensors.h>

const float TurnDegrees::TURN_SPEED = 0.75;

TurnDegrees::TurnDegrees(float degrees, float error)
{
	// Use Requires(&*) here to declare subsystem dependencies
	Requires(&*mobility);

	acceptable_error = error;
	this->degrees = degrees;

	starting_angle = 0.0;
	target_angle = 0.0;

	interrupted = false;
}

// Called just before this Command runs the first time
void TurnDegrees::Initialize()
{
	log->write(Log::TRACE_LEVEL,"TurnDegrees (degrees %f)", degrees);
	starting_angle = sensors->robotAngle();
	target_angle = starting_angle + degrees;

	// make sure target_angle is inside the [-180, 180] range provided by the gyro
	while (target_angle < -180.0)
	{
		target_angle += 360.0;
	}
	while (target_angle > 180.0)
	{
		target_angle -= 360.0;
	}

	interrupted = false;
}

// Called repeatedly when this Command is scheduled to run
void TurnDegrees::Execute()
{
	float current_offset = sensors->robotAngle() - target_angle;

	if ((current_offset < 0.0 && current_offset > -180.0) ||
		(current_offset > 0.0 && current_offset > 180.0))
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

// Make this return true when this Command no longer needs to run execute()
bool TurnDegrees::IsFinished()
{
	if (interrupted)
	{
		return true;
	}

	float current_offset = fabs(sensors->robotAngle() - target_angle);

	if (current_offset < acceptable_error ||
		(360 - current_offset) < acceptable_error)
	{
		return true;
	}

	return false;
}

// Called once after isFinished returns true
void TurnDegrees::End()
{
	log->write(Log::TRACE_LEVEL,"TurnDegres Ended");
	mobility->setStraight(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnDegrees::Interrupted()
{
	log->write(Log::TRACE_LEVEL,"TurnDegrees Interrupted");
	End();
	// Use an interrupted flag instead of setting target_angle to current_angle because
	// our current_angle will change between now and the next IsFinished call
	interrupted = true;
}
