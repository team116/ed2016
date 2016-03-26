#include <Commands/SweepForGoal.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Mobility.h>
#include <Subsystems/Cameras.h>

const float SweepForGoal::TURN_SPEED = 0.75;

SweepForGoal::SweepForGoal(int init_pos)
{
	Requires(&*mobility);
	initial_position = init_pos;
	interrupted = false;
	angle = 0;
}

// Called just before this Command runs the first time
void SweepForGoal::Initialize()
{
	log->write(Log::TRACE_LEVEL,"SweepForGoal Initialized (init_pos %d)", initial_position);
	interrupted = false;
}

// Called repeatedly when this Command is scheduled to run
void SweepForGoal::Execute()
{
	angle = sensors->robotAngle();

	cameras->RefreshContours();
	if (cameras->canSeeGoal())
	{
		mobility->setLeft(0.0);
		mobility->setRight(0.0);
	}
	else if (initial_position == 1)
	{
		if(angle < 40 || angle > 180)
		{
			mobility->setLeft(TURN_SPEED);
			mobility->setRight(-TURN_SPEED);
		}
		else
		{
			mobility->setLeft(-TURN_SPEED);
			mobility->setRight(TURN_SPEED);;
		}
	}
	else if (initial_position == 2)
	{
		if(angle < 26 || angle > 180)
		{
			mobility->setLeft(TURN_SPEED);
			mobility->setRight(-TURN_SPEED);
		}
		else
		{
			mobility->setLeft(-TURN_SPEED);
			mobility->setRight(TURN_SPEED);;
		}
	}
	else if (initial_position == 3)
	{
		if(angle < 12 || angle > 180)
		{
			mobility->setLeft(TURN_SPEED);
			mobility->setRight(-TURN_SPEED);
		}
		else
		{
			mobility->setLeft(-TURN_SPEED);
			mobility->setRight(TURN_SPEED);;
		}
	}
	else if (initial_position == 4)
	{
		if(angle < 180 || angle > 354.8)
		{
			mobility->setLeft(TURN_SPEED);
			mobility->setRight(-TURN_SPEED);
		}
		else
		{
			mobility->setLeft(-TURN_SPEED);
			mobility->setRight(TURN_SPEED);;
		}
	}
	else if (initial_position == 5)
	{
		if(angle < 180 || angle > 339)
		{
			mobility->setLeft(TURN_SPEED);
			mobility->setRight(-TURN_SPEED);
		}
		else
		{
			mobility->setLeft(-TURN_SPEED);
			mobility->setRight(TURN_SPEED);;
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool SweepForGoal::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	else if (cameras->canSeeGoal())
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void SweepForGoal::End()
{
	log->write(Log::TRACE_LEVEL,"SweepForGoal Ended");
	mobility->setLeft(0.0);
	mobility->setRight(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SweepForGoal::Interrupted()
{
	log->write(Log::TRACE_LEVEL,"SweepForGoal Interrupted");
	End();
	interrupted = true;
}
