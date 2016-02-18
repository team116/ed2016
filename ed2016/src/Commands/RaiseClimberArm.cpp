#include <Commands/RaiseClimberArm.h>
#include <Subsystems/Climber.h>

const float RaiseClimberArm::TIMEOUT_1 = 0.5;
const float RaiseClimberArm::TIMEOUT_2 = 3.0;

const float RaiseClimberArm::SPEED_1 = 1.0;
const float RaiseClimberArm::SPEED_2 = 0.5;

RaiseClimberArm::RaiseClimberArm()
{
	Requires(climber);
	interrupted = false;
	temmie = new Timer();
	SetTimeout(3);
}

// Called just before this Command runs the first time
void RaiseClimberArm::Initialize()
{
	temmie->Reset();
}

// Called repeatedly when this Command is scheduled to run
void RaiseClimberArm::Execute()
{
	if(temmie->Get() < TIMEOUT_1)
	{
		climber->setClimber(Climber::CLIMBER_ARM_UP, SPEED_1);
	}
	else if(temmie->Get() < TIMEOUT_2)
	{
		climber->setClimber(Climber::CLIMBER_ARM_UP, SPEED_2);
	}
	else
	{
		climber->setClimber(Climber::CLIMBER_ARM_STILL);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RaiseClimberArm::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	else if (temmie->Get() > TIMEOUT_2)  //(temmie->Get() > TEMMIE_FLAKES)
	{
		return true;
	}
	else if (IsTimedOut())
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void RaiseClimberArm::End()
{
	climber->setClimber(Climber::CLIMBER_ARM_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseClimberArm::Interrupted()
{
	End();
	interrupted = true;
}
