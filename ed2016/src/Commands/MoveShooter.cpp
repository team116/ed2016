#include "MoveShooter.h"
#include <Subsystems/ShooterPitch.h>

MoveShooter::MoveShooter(Utils::VerticalDirection dir)
{
	Requires(&*shooter_pitch);

	direction = dir;
	first_run = true;
}

// Called just before this Command runs the first time
void MoveShooter::Initialize()
{
	//shooter_pitch->Disable();
	shooter_pitch->setDirection(direction);
	first_run = true;
}

// Called repeatedly when this Command is scheduled to run
void MoveShooter::Execute()
{
	first_run = false;
}

// Make this return true when this Command no longer needs to run execute()
bool MoveShooter::IsFinished()
{
	return !first_run && direction == Utils::VerticalDirection::V_STILL;
}

// Called once after isFinished returns true
void MoveShooter::End()
{
	shooter_pitch->setDirection(Utils::VerticalDirection::V_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveShooter::Interrupted()
{
	End();
}
