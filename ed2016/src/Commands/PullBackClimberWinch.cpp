#include "PullBackClimberWinch.h"
#include <Subsystems/Climber.h>

PullBackClimberWinch::PullBackClimberWinch()
{
	Requires(climber);
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void PullBackClimberWinch::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void PullBackClimberWinch::Execute()
{
	climber->setBackWinch(Climber::WinchDirection::ROBOT_PULL_DOWN);
}

// Make this return true when this Command no longer needs to run execute()
bool PullBackClimberWinch::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void PullBackClimberWinch::End()
{
	climber->setBackWinch(Climber::WinchDirection::ROBOT_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PullBackClimberWinch::Interrupted()
{
	End();
}
