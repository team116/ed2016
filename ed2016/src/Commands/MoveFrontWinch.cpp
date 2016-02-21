#include "MoveFrontWinch.h"

MoveFrontWinch::MoveFrontWinch(Utils::VerticalDirection dir)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(&*climber);

	movement_direction = dir;
}

// Called just before this Command runs the first time
void MoveFrontWinch::Initialize()
{
	climber->setFrontWinchDirection(movement_direction);
}

// Called repeatedly when this Command is scheduled to run
void MoveFrontWinch::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool MoveFrontWinch::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MoveFrontWinch::End()
{
	climber->setFrontWinchDirection(Utils::VerticalDirection::V_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveFrontWinch::Interrupted()
{
	End();
}
