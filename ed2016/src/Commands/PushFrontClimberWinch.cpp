#include "PushFrontClimberWinch.h"
#include <Subsystems/Climber.h>

PushFrontClimberWinch::PushFrontClimberWinch()
{
	Requires(climber);
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void PushFrontClimberWinch::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void PushFrontClimberWinch::Execute()
{
	climber->setFrontWinch(Climber::WinchDirection::ROBOT_PULL_UP); //maybe change the name pull_up yeah?
}

// Make this return true when this Command no longer needs to run execute()
bool PushFrontClimberWinch::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void PushFrontClimberWinch::End()
{
	climber->setFrontWinch(Climber::WinchDirection::ROBOT_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PushFrontClimberWinch::Interrupted()
{
	End();
}
