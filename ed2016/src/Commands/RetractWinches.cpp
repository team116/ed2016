#include <Commands/RetractWinches.h>
#include <Subsystems/Climber.h>

const float RetractWinches::ARM_TIMEOUT = 3.0;
const float RetractWinches::WINCH_TIMEOUT = 3.0;

RetractWinches::RetractWinches()
{
	Requires(climber);
	temmie = new Timer();

	interrupted = false;
}

// Called just before this Command runs the first time
void RetractWinches::Initialize()
{
	temmie->Reset();
}

// Called repeatedly when this Command is scheduled to run
void RetractWinches::Execute()
{
	if (temmie->Get() < ARM_TIMEOUT)
	{
		climber->setClimber(Climber::CLIMBER_ARM_DOWN);
	}
	else
	{
		climber->setClimber(Climber::CLIMBER_ARM_STILL);
	}

	if (temmie->Get() < WINCH_TIMEOUT)
	{
		climber->setFrontWinch(Climber::ROBOT_PULL_UP);
		climber->setBackWinch(Climber::ROBOT_PULL_UP);
	}
	else
	{
		climber->setFrontWinch(Climber::ROBOT_STILL);
		climber->setBackWinch(Climber::ROBOT_STILL);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RetractWinches::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	else if (temmie->Get() > ARM_TIMEOUT && temmie->Get() > WINCH_TIMEOUT)
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void RetractWinches::End()
{
	climber->setClimber(Climber::CLIMBER_ARM_STILL);

	climber->setFrontWinch(Climber::ROBOT_STILL);
	climber->setBackWinch(Climber::ROBOT_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RetractWinches::Interrupted()
{
	End();
	interrupted = true;
}
