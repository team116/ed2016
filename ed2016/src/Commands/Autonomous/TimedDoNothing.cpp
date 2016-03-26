#include "TimedDoNothing.h"
#include <Subsystems/Mobility.h>

TimedDoNothing::TimedDoNothing(float timeout)
{
	Requires(&*mobility);

	SetTimeout(timeout);
}

// Called just before this Command runs the first time
void TimedDoNothing::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void TimedDoNothing::Execute()
{
	mobility->setStraight(0.0);
}

// Make this return true when this Command no longer needs to run execute()
bool TimedDoNothing::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void TimedDoNothing::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TimedDoNothing::Interrupted()
{
	End();
}
