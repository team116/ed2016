#include "MoveClimberArm.h"

MoveClimberArm::MoveClimberArm(Utils::VerticalDirection dir)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(&*climber);

	movement_direction = dir;
}

// Called just before this Command runs the first time
void MoveClimberArm::Initialize()
{
	climber->setClimber(movement_direction);
}

// Called repeatedly when this Command is scheduled to run
void MoveClimberArm::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool MoveClimberArm::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MoveClimberArm::End()
{
	climber->setClimber(Utils::VerticalDirection::V_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveClimberArm::Interrupted()
{
	End();
}
