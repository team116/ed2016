#include "DriveDistance.h"
#include <Subsystems/Mobility.h>
#include <Subsystems/Sensors.h>

DriveDistance::DriveDistance(float dist)
{
	Requires(mobility);
	distance = dist;
}

// Called just before this Command runs the first time
void DriveDistance::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DriveDistance::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistance::Interrupted()
{

}
