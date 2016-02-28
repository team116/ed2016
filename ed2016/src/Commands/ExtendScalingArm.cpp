#include <Commands/ExtendScalingArm.h>
#include <Subsystems/Climber.h>
#include <Subsystems/ShooterPitch.h>

const float ExtendScalingArm::TIMEOUT_1 = 3.0;
const float ExtendScalingArm::TIMEOUT_2 = 10.0;
const float ExtendScalingArm::SHOOTER_TIMEOUT = 2.0;

const float ExtendScalingArm::SPEED_1 = 1.0;
const float ExtendScalingArm::SPEED_2 = 0.5;

const float ExtendScalingArm::SHOOTER_ERROR = 0.5;

ExtendScalingArm::ExtendScalingArm()
{
	Requires(&*climber);
	Requires(&*shooter_pitch);
	interrupted = false;
	shooter_ready = false;
	temmie = new Timer();
	temmie_sp = new Timer();
}

// Called just before this Command runs the first time
void ExtendScalingArm::Initialize()
{
	log->write(Log::TRACE_LEVEL, "ExtendScalingArm Initialized");
	interrupted = false;
	temmie->Reset();
	temmie_sp->Reset();
	temmie_sp->Start();

	shooter_ready = sensors->shooterAngle() < SHOOTER_ERROR;
}

// Called repeatedly when this Command is scheduled to run
void ExtendScalingArm::Execute()
{

	//Move shooter out of the way
	if (!shooter_ready && temmie_sp->Get() < SHOOTER_TIMEOUT)
	{
		shooter_pitch->setShooterPitchDirection(ShooterPitch::SHOOTER_DOWN);
	}
	else if (temmie->Get() == 0 && (shooter_ready || temmie_sp->Get() > SHOOTER_TIMEOUT))
	{
		shooter_pitch->setShooterPitchDirection(ShooterPitch::SHOOTER_STILL);
		shooter_ready = true;
		temmie->Reset();
		temmie->Start();
	}


	if((temmie->Get() < TIMEOUT_1) && shooter_ready)
	{
		climber->setClimber(Utils::VerticalDirection::UP, SPEED_1);
	}
	else if((temmie->Get() < TIMEOUT_2) && shooter_ready)
	{
		climber->setClimber(Utils::VerticalDirection::UP, SPEED_2);
	}
	else
	{
		climber->setClimber(Utils::VerticalDirection::V_STILL);
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
	else if (climber->isClimberCurrentSpiking())
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void ExtendScalingArm::End()
{
	log->write(Log::TRACE_LEVEL, "ExtendScalingArm Ended");
	climber->setClimber(Utils::VerticalDirection::V_STILL);
	shooter_pitch->setShooterPitchDirection(ShooterPitch::SHOOTER_STILL);
	temmie->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendScalingArm::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "ExtendScalingArm Interrupted");
	End();
	interrupted = true;
}
