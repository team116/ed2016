#include <CheckManualOverrides.h>
#include <Commands/MoveShooterToZero.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/ShooterPitch.h>

MoveShooterToZero::MoveShooterToZero()
{
	Requires(&*shooter_pitch);
	pid_was_enabled = false;
}

// Called just before this Command runs the first time
void MoveShooterToZero::Initialize()
{
	log->write(Log::TRACE_LEVEL, "MoveShooterToZero initialized");
	pid_was_enabled = shooter_pitch->isPIDEnabled();

	if (pid_was_enabled)
	{
		CheckManualOverrides::requestPIDEnable(&*shooter_pitch, false);
	}
}

// Called repeatedly when this Command is scheduled to run
void MoveShooterToZero::Execute()
{
	shooter_pitch->setDirection(Utils::VerticalDirection::DOWN);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveShooterToZero::IsFinished()
{
	return sensors->isShooterHomeSwitchHorizontal();
}

// Called once after isFinished returns true
void MoveShooterToZero::End()
{
	log->write(Log::TRACE_LEVEL, "MoveShooterToZero ended");
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
