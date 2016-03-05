#include "MoveShooter.h"
#include <Subsystems/ShooterPitch.h>

MoveShooter::MoveShooter(Utils::VerticalDirection dir)
{
	Requires(&*shooter_pitch);

	direction = dir;
}

// Called just before this Command runs the first time
void MoveShooter::Initialize()
{
	//shooter_pitch->Disable();
	shooter_pitch->setShooterPitchDirection(direction);
}

// Called repeatedly when this Command is scheduled to run
void MoveShooter::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool MoveShooter::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MoveShooter::End()
{
	shooter_pitch->setShooterPitchDirection(Utils::VerticalDirection::V_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveShooter::Interrupted()
{
	End();
}
