#include "LowerClimberArm.h"
#include <Subsystems/Climber.h>

LowerClimberArm::LowerClimberArm()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(climber);
}

// Called just before this Command runs the first time
void LowerClimberArm::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void LowerClimberArm::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LowerClimberArm::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void LowerClimberArm::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerClimberArm::Interrupted()
{

}
