#include "RaiseClimberArm.h"
#include <Subsystems/Climber.h>

RaiseClimberArm::RaiseClimberArm()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(climber);
}

// Called just before this Command runs the first time
void RaiseClimberArm::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RaiseClimberArm::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool RaiseClimberArm::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RaiseClimberArm::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseClimberArm::Interrupted()
{

}
