#include <Commands/Shoot.h>
#include <OI.h>
#include <Subsystems/Shooter.h>
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
	set_wheels = false;
}

// Called just before this Command runs the first time
void Shoot::Initialize()
{
	log->write(Log::TRACE_LEVEL,"Shoot Initialized");
	interrupted = false;
	past_speed_up_time = false;
	timer->Start();
	timer->Reset();

	if((shooter->GetSetpoint() != 0.0) || (shooter->getMotorSpeed() != 0.0)) {
		set_wheels = false;
	}
	else {
		set_wheels = true;
	}
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute()
{
	if(set_wheels) {
		float ideal_speed = shooter->getRPMPreset(oi->getShooterSpeedPosition());
		shooter->setRPM(ideal_speed);

		if (!past_speed_up_time && (sensors->speedShooterWheel() > ideal_speed || timer->Get() > SPEED_UP_TIME))
		{
			past_speed_up_time = true;
			holder_wheel->setWheelDirection(Utils::HorizontalDirection::IN);
			timer->Reset();
		}
	}
	else {
		past_speed_up_time = true;
		holder_wheel->setWheelDirection(Utils::HorizontalDirection::IN);
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
	oi->resetIntakeDirectionSwitch();
	shooter->setSpeed(0.0);
	oi->updateAngle();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted()
{
	log->write(Log::TRACE_LEVEL,"Shoot Interrupted");
	interrupted = true;
	End();
}
