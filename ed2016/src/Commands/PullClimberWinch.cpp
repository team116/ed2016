#include <Commands/PullClimberWinch.h>

OperateClimberWinch::OperateClimberWinch(Climber::WinchDirection direction)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(climber);

	winch_direction = direction;
}

// Called just before this Command runs the first time
void OperateClimberWinch::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void OperateClimberWinch::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool OperateClimberWinch::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void OperateClimberWinch::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperateClimberWinch::Interrupted()
{

}
