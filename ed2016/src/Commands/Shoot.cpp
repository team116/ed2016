#include <Commands/Shoot.h>
#include <OI.h>
#include <Subsystems/ShooterPID.h>
#include <Subsystems/HolderWheel.h>
#include <Subsystems/Sensors.h>

const float Shoot::SPEED_UP_TIME = 5.0;
const float Shoot::PUSH_BOULDER = 2.0;

Shoot::Shoot() : CommandBase("Shoot")
{
	Requires(&*shooter);
	Requires(&*holder_wheel);

	timer = new Timer();
	interrupted = false;
	past_speed_up_time = false;
}

// Called just before this Command runs the first time
void Shoot::Initialize()
{
	log->write(Log::TRACE_LEVEL,"Shoot Initialized");
	interrupted = false;
	past_speed_up_time = false;
	timer->Start();
	timer->Reset();
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute()
{
	float ideal_speed = shooter->getRPMPreset(oi->getShooterSpeedPosition());
	//shooter->setShooterSpeed(shooter->getSpeedPreset(oi->getShooterSpeedPosition()));

	if (!past_speed_up_time && (sensors->speedShooterWheel() > ideal_speed || timer->Get() > SPEED_UP_TIME))
	{
		past_speed_up_time = true;
		holder_wheel->setWheelDirection(Utils::HorizontalDirection::IN);
		timer->Reset();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	if (past_speed_up_time && (timer->Get() > PUSH_BOULDER))
	{
		log->write(Log::TRACE_LEVEL, "Shoot timed out (tach rate %f)", sensors->speedShooterWheel());
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void Shoot::End()
{
	log->write(Log::TRACE_LEVEL,"Shoot Ended");
	holder_wheel->setWheelDirection(oi->getIntakeDirectionSwitch());
	shooter->setShooterSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted()
{
	log->write(Log::TRACE_LEVEL,"Shoot Interrupted");
	interrupted = true;
	End();
}
