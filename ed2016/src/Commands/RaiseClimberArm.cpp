#include "RaiseClimberArm.h"
#include <Subsystems/Climber.h>
#include <Timer.h>

RaiseClimberArm::RaiseClimberArm()
{
	// Use Requires(&*) here to declare subsystem dependencies
	// eg. Requires(&*chassis);
	Requires(&*climber);
}

// Called just before this Command runs the first time
void RaiseClimberArm::Initialize()
{
	temmie->Reset();
	temmie->Start();
}

// Called repeatedly when this Command is scheduled to run
void RaiseClimberArm::Execute()
{
	climber->setClimber(Climber::CLIMBER_ARM_UP );
	if (temmie->HasPeriodPassed(0))	//put the time it takes to raise arm here
	{
		climber->setClimber(Climber::CLIMBER_ARM_STILL);
		climber->setFrontWinch(Climber::ROBOT_PULL_UP);
		climber->setBackWinch(Climber::ROBOT_PULL_UP);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool RaiseClimberArm::IsFinished()
{
	if(temmie->HasPeriodPassed(0))//Put Olivia's winch motor current detector here
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void RaiseClimberArm::End()
{
	climber->setFrontWinch(Climber::ROBOT_STILL);
	climber->setBackWinch(Climber::ROBOT_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseClimberArm::Interrupted()
{
	End();
}
