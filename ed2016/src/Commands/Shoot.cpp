#include <Commands/Shoot.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/HolderWheel.h>

const float Shoot::SPEED_UP_TIME = 1.0;
const float Shoot::PUSH_BOULDER = 1.5;

Shoot::Shoot()
{
	Requires(shooter);
	Requires(holderwheel);

	timer = new Timer();
	interrupted = false;
}

// Called just before this Command runs the first time
void Shoot::Initialize()
{
	timer->Start();
	timer->Reset();
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute()
{
	shooter->turnShooterOn(true);

	if (timer->HasPeriodPassed(SPEED_UP_TIME))
	{
		holderwheel->turnHolderWheelOn(true);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	if (timer->HasPeriodPassed(PUSH_BOULDER))
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void Shoot::End()
{
	shooter->turnShooterOn(false);
	holderwheel->turnHolderWheelOn(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted()
{
	interrupted = true;
}
