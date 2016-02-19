#include <Commands/DriveByLidar.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Mobility.h>

DriveByLidar::DriveByLidar(float dist, float err)
{
	Requires(&*mobility);
	target_distance = dist;
	distance = 0;
	error = err;
	interrupted = false;
}

// Called just before this Command runs the first time
void DriveByLidar::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DriveByLidar::Execute()
{
	distance = sensors->lidarDistance();
	if (distance < target_distance - error)
	{
		mobility->setStraight(1.0);
	}
	else if (distance > target_distance + error)
	{
		mobility->setStraight(-1.0);
	}
	else
	{
		mobility->setStraight(0.0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DriveByLidar::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	else if (distance > target_distance - error && distance < target_distance + error)
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void DriveByLidar::End()
{
	mobility->setStraight(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveByLidar::Interrupted()
{
	End();
	interrupted = true;
}
