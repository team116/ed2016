#include <Commands/ContinuousTurn.h>
#include <Subsystems/Mobility.h>

const float ContinuousTurn::TURN_SPEED = 0.75;

ContinuousTurn::ContinuousTurn(ContinuousTurn::Direction dir)
{
	Requires(mobility);
	direction = dir;
	interrupted = false;
}

// Called just before this Command runs the first time
void ContinuousTurn::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ContinuousTurn::Execute()
{
	if (direction == RIGHT)
	{
		mobility->setLeft(TURN_SPEED);
		mobility->setRight(-TURN_SPEED);
	}
	else if (direction == LEFT)
	{
		mobility->setLeft(-TURN_SPEED);
		mobility->setRight(TURN_SPEED);
	}
	else
	{
		mobility->setLeft(0.0);
		mobility->setRight(0.0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ContinuousTurn::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void ContinuousTurn::End()
{
	mobility->setLeft(0.0);
	mobility->setRight(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ContinuousTurn::Interrupted()
{
	End();
	interrupted = true;
}
