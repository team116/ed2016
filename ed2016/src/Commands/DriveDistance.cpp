#include "DriveDistance.h"
#include <Subsystems/Mobility.h>
#include <Subsystems/Sensors.h>
#include <Commands/DriveStraight.h>

const float DriveDistance::DRIVE_DISTANCE_TIMEOUT = 1.0/30.0;

DriveDistance::DriveDistance(float dist)
{
	Requires(&*mobility);
	distance = dist;
	starting_distance = (sensors->getDistanceLeft() + sensors->getDistanceRight())/2.0;
	current_distance = starting_distance;
	dir = 0.0;
	interrupted = false;

	auto_drive_straight = new DriveStraight(0.5, DriveStraight::GYRO);

	timeout = dist * DRIVE_DISTANCE_TIMEOUT;

	temmie = new Timer();

}

// Called just before this Command runs the first time
void DriveDistance::Initialize()
{
	DriverStation::ReportError("DriveDistance started");
	log->write(Log::TRACE_LEVEL, "DriveDistance Initialized (distance, %f)", distance);
	interrupted = false;
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

	Scheduler::GetInstance()->AddCommand(auto_drive_straight);


	temmie->Reset();
	temmie->Start();

}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute()
{
	current_distance = (sensors->getDistanceLeft() + sensors->getDistanceRight())/2.0 - starting_distance;
	mobility->setStraight(dir);

}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished()
{

	if(temmie->Get() >= timeout)
	{
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
	log->write(Log::TRACE_LEVEL, "DriveDistance Ended");
	mobility->setStraight(0.0);
	auto_drive_straight->Interrupted();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistance::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "DriveDistance Interrupted");
	End();
	interrupted = true;
}
