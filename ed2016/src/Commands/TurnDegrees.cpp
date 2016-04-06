#include <cmath>
#include <Commands/TurnDegrees.h>
#include <Subsystems/Mobility.h>
#include <Subsystems/Sensors.h>

const float TurnDegrees::TURN_SPEED = 0.50;

TurnDegrees::TurnDegrees(float degrees, float error)
{
	// Use Requires(&*) here to declare subsystem dependencies

	Requires(&*mobility);

	acceptable_error = error;
	this->degrees = degrees;

	starting_angle = 0.0;
	target_angle = 0.0;

	current_clockwise_offset = 0.0;
	current_counter_offset = -0.0;
	interrupted = false;
}

// Called just before this Command runs the first time
void TurnDegrees::Initialize()
{
	log->write(Log::INFO_LEVEL,"TurnDegrees (degrees %f)", degrees);
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

	log->write(Log::INFO_LEVEL,"CURRENT ANGLE = %f, TARGET ANGLE = %f", starting_angle, target_angle);
	interrupted = false;
}

// Called repeatedly when this Command is scheduled to run
void TurnDegrees::Execute()
{
	float current_angle = sensors->robotAngle();

	current_clockwise_offset = target_angle - current_angle;
	current_counter_offset = current_angle - target_angle;

	if (current_angle < target_angle)
	{
		current_counter_offset = -current_counter_offset;
		current_clockwise_offset = -current_clockwise_offset;
	}

	if(fabs(current_counter_offset) < fabs(current_clockwise_offset))
	{
		mobility->setLeft(-TURN_SPEED * fabs(current_counter_offset) / degrees);
		mobility->setRight(TURN_SPEED * fabs(current_counter_offset) / degrees);
		direction_turning = CurrentDirection::COUNTERCLOCKWISE;
	}
		else
		{
			mobility->setRight(-TURN_SPEED * fabs(current_clockwise_offset) / degrees);
			mobility->setLeft(TURN_SPEED * fabs(current_clockwise_offset) / degrees);
			direction_turning = CurrentDirection::CLOCKWISE;
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
	log->write(Log::INFO_LEVEL,"TurnDegrees CURRENT OFFSET = %f", current_offset);

	if (direction_turning == CurrentDirection::CLOCKWISE)
	{
		if (fabs(current_clockwise_offset) < acceptable_error)

		return true;
	}

	else if(direction_turning == CurrentDirection::COUNTERCLOCKWISE)
	{
		if(fabs(current_counter_offset) < acceptable_error)

		return true;
	}
	return false;
}


// Called once after isFinished returns true
void TurnDegrees::End()
{
	log->write(Log::INFO_LEVEL,"TurnDegres Ended");
	mobility->setStraight(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnDegrees::Interrupted()
{
	log->write(Log::INFO_LEVEL,"TurnDegrees Interrupted");
	End();
	// Use an interrupted flag instead of setting target_angle to current_angle because
	// our current_angle will change between now and the next IsFinished call
	interrupted = true;
}
