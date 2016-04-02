#include "MoveShooter.h"
#include <Subsystems/Sensors.h>
#include <Subsystems/ShooterPitch.h>

MoveShooter::MoveShooter(Utils::VerticalDirection dir)
{
	Requires(&*shooter_pitch);

	direction = dir;
	enable_pid = false;
}

// Called just before this Command runs the first time
void MoveShooter::Initialize()
{
	enable_pid = shooter_pitch->isPIDEnabled();
	shooter_pitch->Disable();

	shooter_pitch->setDirection(direction);

	switch (direction)
	{
	case Utils::VerticalDirection::UP:
		log->write(Log::ERROR_LEVEL, "MoveShooter initialized UP");
		break;
	case Utils::VerticalDirection::V_STILL:
		log->write(Log::ERROR_LEVEL, "MoveShooter initialized V_STILL");
		break;
	case Utils::VerticalDirection::DOWN:
		log->write(Log::ERROR_LEVEL, "MoveShooter initialized DOWN");
		break;
	}
}

// Called repeatedly when this Command is scheduled to run
void MoveShooter::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool MoveShooter::IsFinished()
{
	return direction == Utils::VerticalDirection::V_STILL;
}

// Called once after isFinished returns true
void MoveShooter::End()
{
	shooter_pitch->setDirection(Utils::VerticalDirection::V_STILL);

	if (enable_pid && sensors->areShooterAngleEnabled())
	{
		shooter_pitch->Enable();
		shooter_pitch->SetSetpoint(sensors->shooterAngle());
	}
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveShooter::Interrupted()
{
	End();
}
