#include "CheckLidar.h"
#include <Subsystems/Sensors.h>
CheckLidar::CheckLidar()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(sensors);
}

// Called just before this Command runs the first time
void CheckLidar::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CheckLidar::Execute()
{
	sensors->refreshLidar();
}

// Make this return true when this Command no longer needs to run execute()
bool CheckLidar::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CheckLidar::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CheckLidar::Interrupted()
{

}
