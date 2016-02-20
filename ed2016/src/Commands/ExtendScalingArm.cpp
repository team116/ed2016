#include <Commands/ExtendScalingArm.h>
#include <Subsystems/Climber.h>
#include <Subsystems/Shooter.h>

const float ExtendScalingArm::TIMEOUT_1 = 0.5;
const float ExtendScalingArm::TIMEOUT_2 = 3.0;

const float ExtendScalingArm::SPEED_1 = 1.0;
const float ExtendScalingArm::SPEED_2 = 0.5;

const float ExtendScalingArm::SHOOTER_ERROR = 0.5;

ExtendScalingArm::ExtendScalingArm()
{
	Requires(&*climber);
	Requires(&*shooter);
	interrupted = false;
	temmie = new Timer();
}

// Called just before this Command runs the first time
void ExtendScalingArm::Initialize()
{
	temmie->Reset();
}

// Called repeatedly when this Command is scheduled to run
void ExtendScalingArm::Execute()
{
	bool shooter_ready = sensors->shooterAngle() < SHOOTER_ERROR;

	if (!shooter_ready)
	{
		shooter->setShooterPitchDirection(Shooter::SHOOTER_DOWN);
	}
	else if (temmie->Get() == 0)
	{
		temmie->Start();
	}

	if(temmie->Get() < TIMEOUT_1 && shooter_ready)
	{
		climber->setClimber(Climber::CLIMBER_ARM_UP, SPEED_1);
	}
	else if(temmie->Get() < TIMEOUT_2 && shooter_ready)
	{
		climber->setClimber(Climber::CLIMBER_ARM_UP, SPEED_2);
	}
	else
	{
		climber->setClimber(Climber::CLIMBER_ARM_STILL);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendScalingArm::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	else if (temmie->Get() > TIMEOUT_2)
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void ExtendScalingArm::End()
{
	climber->setClimber(Climber::CLIMBER_ARM_STILL);
	temmie->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendScalingArm::Interrupted()
{
	End();
	interrupted = true;
}
