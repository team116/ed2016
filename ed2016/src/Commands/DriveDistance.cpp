#include "DriveDistance.h"
#include <Subsystems/Mobility.h>
#include <Subsystems/Sensors.h>

DriveDistance::DriveDistance(float dist)
{
	Requires(mobility);
	distance = dist;
	starting_distance = (sensors->getDistanceLeft() + sensors->getDistanceRight())/2.0;
	current_distance = starting_distance;
}

// Called just before this Command runs the first time
void DriveDistance::Initialize()
{
	if (distance > 0)
	{
		mobility->setStraight(1.0);
	}
	else if (distance < 0)
	{
		mobility->setStraight(-1.0);
	}
	else
	{
		mobility->setStraight(0.0);
	}
}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute()
{
	current_distance = (sensors->getDistanceLeft() + sensors->getDistanceRight())/2.0;
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished()
{
	if((current_distance - starting_distance >= distance && distance > 0) || (current_distance - starting_distance <= distance && distance < 0) || distance == 0) {
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
	//I'm not sure if I should set the motors to 0 here or not
}
