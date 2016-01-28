#include "AutoClimb.h"
#include <Subsystems/Climber.h>

AutoClimb::AutoClimb()
{
	Requires(climber);
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void AutoClimb::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void AutoClimb::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool AutoClimb::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void AutoClimb::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoClimb::Interrupted()
{

}
