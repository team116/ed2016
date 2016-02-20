#include "PushBackClimberWinch.h"
#include <Subsystems/Climber.h>

PushBackClimberWinch::PushBackClimberWinch()
{
	Requires(&*climber);
	// Use Requires(&*) here to declare subsystem dependencies
	// eg. Requires(&*chassis);
}

// Called just before this Command runs the first time
void PushBackClimberWinch::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void PushBackClimberWinch::Execute()
{
	climber->setBackWinch(Climber::WinchDirection::ROBOT_PULL_UP);
}

// Make this return true when this Command no longer needs to run execute()
bool PushBackClimberWinch::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void PushBackClimberWinch::End()
{
	climber->setBackWinch(Climber::WinchDirection::ROBOT_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PushBackClimberWinch::Interrupted()
{
	End();
}
