#include "AutoClimb.h"
#include <Subsystems/Climber.h>

const float AutoClimb::CLIMBER_TIMEOUT = 1.0; //TODO: change later
AutoClimb::AutoClimb()
{
	Requires(climber);
	SetTimeout(CLIMBER_TIMEOUT);
	interrupted = false;
}

// Called just before this Command runs the first time
void AutoClimb::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void AutoClimb::Execute()
{
	climber->setClimber(Climber::CLIMBER_ARM_DOWN);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoClimb::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void AutoClimb::End()
{
	climber->setClimber(Climber::CLIMBER_ARM_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoClimb::Interrupted()
{
	End();
	interrupted = true;
}
