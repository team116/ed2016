#include <Commands/Shoot.h>
#include <OI.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/HolderWheel.h>
#include <Subsystems/Sensors.h>

const float Shoot::SPEED_UP_TIME = 1.0;
const float Shoot::PUSH_BOULDER = 0.5;

Shoot::Shoot() : CommandBase("Shoot")
{
	Requires(&*shooter);
	Requires(&*holder_wheel);

	timer = new Timer();
	interrupted = false;
}

// Called just before this Command runs the first time
void Shoot::Initialize()
{
	interrupted = false;
	timer->Start();
	timer->Reset();
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute()
{
	float ideal_speed = shooter->getRPMPreset(oi->getShooterSpeedPosition());
	shooter->setShooterSpeed(shooter->getSpeedPreset(oi->getShooterSpeedPosition()));

	if ((sensors->speedTopShooterWheel() > ideal_speed && sensors->speedBottomShooterWheel() > ideal_speed) ||
		 timer->Get() > SPEED_UP_TIME)
	{
		holder_wheel->setWheelDirection(Utils::HorizontalDirection::OUT);
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
	if ((holder_wheel->getWheelDirection() == Utils::HorizontalDirection::OUT) && (timer->Get() > PUSH_BOULDER))
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void Shoot::End()
{
	holder_wheel->setWheelDirection(Utils::HorizontalDirection::H_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted()
{
	interrupted = true;
	End();
}
