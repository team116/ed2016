#include <Commands/RetractWinches.h>
#include <Subsystems/Climber.h>

const float RetractWinches::ARM_TIMEOUT = 3.0;
const float RetractWinches::WINCH_TIMEOUT = 3.0;
const float RetractWinches::CURRENT_SPIKE_TIMEOUT = 2.0;

RetractWinches::RetractWinches()
{
	Requires(&*climber);
	temmie_a = new Timer();
	temmie_w = new Timer();

	interrupted = false;
}

// Called just before this Command runs the first time
void RetractWinches::Initialize()
{
	interrupted = false;
	temmie_a->Reset();
	temmie_w->Reset();
	temmie_w->Start();
}

// Called repeatedly when this Command is scheduled to run
void RetractWinches::Execute()
{
	if(climber->isWinchCurrentSpiking() || temmie_w->Get() > CURRENT_SPIKE_TIMEOUT)
	{
		temmie_a->Start();
	}

	if (temmie_a->Get() < ARM_TIMEOUT && temmie_a->Get() > 0.0)
	{
		climber->setClimber(Climber::CLIMBER_ARM_DOWN);
	}
	else
	{
		climber->setClimber(Climber::CLIMBER_ARM_STILL);
	}



	if (temmie_w->Get() < WINCH_TIMEOUT)
	{
		climber->setFrontWinchDirection(Climber::ROBOT_PULL_UP);
		climber->setBackWinchDirection(Climber::ROBOT_PULL_UP);
	}
	else
	{
		climber->setFrontWinchDirection(Climber::ROBOT_STILL);
		climber->setBackWinchDirection(Climber::ROBOT_STILL);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RetractWinches::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	else if (temmie_a->Get() > ARM_TIMEOUT && temmie_w->Get() > WINCH_TIMEOUT)
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void RetractWinches::End()
{
	climber->setClimber(Climber::CLIMBER_ARM_STILL);

	climber->setFrontWinchDirection(Climber::ROBOT_STILL);
	climber->setBackWinchDirection(Climber::ROBOT_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RetractWinches::Interrupted()
{
	End();
	interrupted = true;
}

