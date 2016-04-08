#include <CheckManualOverrides.h>
#include <Commands/MoveShooterToZero.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/ShooterPitch.h>

const float MoveShooterToZero::EXTRA_BACKDRIVE_TIMEOUT = 0.25;

MoveShooterToZero::MoveShooterToZero()
{
	Requires(&*shooter_pitch);
	extra_backdrive_timer = new Timer();
	pid_was_enabled = false;
	last_switch_value = false;
}

// Called just before this Command runs the first time
void MoveShooterToZero::Initialize()
{
	log->write(Log::TRACE_LEVEL, "MoveShooterToZero initialized");
	pid_was_enabled = shooter_pitch->isPIDEnabled();
	last_switch_value = false;

	if (pid_was_enabled)
	{
		CheckManualOverrides::requestPIDEnable(&*shooter_pitch, false);
	}
}

// Called repeatedly when this Command is scheduled to run
void MoveShooterToZero::Execute()
{
	shooter_pitch->setDirection(Utils::VerticalDirection::DOWN);

	/*
	bool switch_value = sensors->isShooterHomeSwitchHorizontal();
	if (switch_value && switch_value != last_switch_value)
	{
		last_switch_value = true;
		extra_backdrive_timer->Start();
		extra_backdrive_timer->Reset();
	}
	*/
}

// Make this return true when this Command no longer needs to run execute()
bool MoveShooterToZero::IsFinished()
{
	return sensors->isShooterHomeSwitchHorizontal() /*&& extra_backdrive_timer->Get() > EXTRA_BACKDRIVE_TIMEOUT*/;
}

// Called once after isFinished returns true
void MoveShooterToZero::End()
{
	log->write(Log::TRACE_LEVEL, "MoveShooterToZero ended");
	extra_backdrive_timer->Stop();
	if (pid_was_enabled)
	{
		CheckManualOverrides::requestPIDEnable(&*shooter_pitch, true);
		shooter_pitch->setAngle(sensors->shooterAngle());
	}
	pid_was_enabled = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveShooterToZero::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "MoveShooterToZero interrupted");
	End();
}
