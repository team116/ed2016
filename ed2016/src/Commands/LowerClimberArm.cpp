#include "LowerClimberArm.h"
#include <Subsystems/Climber.h>
#include <Timer.h>

LowerClimberArm::LowerClimberArm()
{
	// Use Requires(&*) here to declare subsystem dependencies
	// eg. Requires(&*chassis);
	Requires(&*climber);
	temmie = new Timer();
}

// Called just before this Command runs the first time
void LowerClimberArm::Initialize()
{
	temmie->Reset();
}

// Called repeatedly when this Command is scheduled to run
void LowerClimberArm::Execute()
{
	climber->setFrontWinch(Climber::ROBOT_PULL_DOWN);
	climber->setBackWinch(Climber::ROBOT_PULL_DOWN);
	if(temmie->HasPeriodPassed(0)) //Put Olivia's winch motor current detector here
	{
		temmie->Start();
		climber->setClimber(Climber::CLIMBER_ARM_DOWN);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool LowerClimberArm::IsFinished()
{
	if(temmie->HasPeriodPassed(0)) //put the time it takes to raise arm here
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void LowerClimberArm::End()
{
	climber->setClimber(Climber::CLIMBER_ARM_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerClimberArm::Interrupted()
{
	End();
}
