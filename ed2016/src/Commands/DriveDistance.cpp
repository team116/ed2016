#include "DriveDistance.h"
#include <Subsystems/Mobility.h>
#include <Subsystems/Sensors.h>

const float DriveDistance::DRIVE_DISTANCE_TIMEOUT = 1.0;

DriveDistance::DriveDistance(float dist)
{
	Requires(&*mobility);
	distance = dist;
	starting_distance = (sensors->getDistanceLeft() + sensors->getDistanceRight())/2.0;
	current_distance = starting_distance;
	dir = 0.0;
	interrupted = false;
	SetTimeout(dist * DRIVE_DISTANCE_TIMEOUT);
}

// Called just before this Command runs the first time
void DriveDistance::Initialize()
{
	if (distance > 0)
	{
		dir = 1.0;
	}
	else if (distance < 0)
	{
		dir = -1.0;
	}
	else
	{
		dir = 0.0;
	}
}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute()
{
	current_distance = (sensors->getDistanceLeft() + sensors->getDistanceRight())/2.0;
	mobility->setStraight(dir);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished()
{

	if(IsTimedOut())
	{
		DriverStation::ReportError("DriveDistance HasTimedOut");
		return true;
	}
	if(interrupted)
	{
		return true;
	}
	if((distance == 0 ||
			(current_distance - starting_distance >= distance && distance > 0)) ||
			(current_distance - starting_distance <= distance && distance < 0))
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void DriveDistance::End()
{
	mobility->setStraight(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistance::Interrupted()
{
	End();
	interrupted = true;
}
