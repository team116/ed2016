#include <Commands/PullFrontClimberWinch.h>
#include <Subsystems/Climber.h>

PullFrontClimberWinch::PullFrontClimberWinch()
{
	Requires(climber);
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void PullFrontClimberWinch::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void PullFrontClimberWinch::Execute()
{
	climber->setFrontWinch(Climber::WinchDirection::ROBOT_PULL_DOWN);
}

// Make this return true when this Command no longer needs to run execute()
bool PullFrontClimberWinch::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void PullFrontClimberWinch::End()
{
	climber->setFrontWinch(Climber::WinchDirection::ROBOT_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PullFrontClimberWinch::Interrupted()
{
	End();
}
