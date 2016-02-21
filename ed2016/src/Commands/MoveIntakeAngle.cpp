#include "MoveIntakeAngle.h"

MoveIntakeAngle::MoveIntakeAngle(Utils::VerticalDirection dir)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(&*intake);

	movement_direction = dir;
}

// Called just before this Command runs the first time
void MoveIntakeAngle::Initialize()
{
	intake->setIntakeAngleDirection(movement_direction);
}

// Called repeatedly when this Command is scheduled to run
void MoveIntakeAngle::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool MoveIntakeAngle::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MoveIntakeAngle::End()
{
	intake->setIntakeAngleDirection(Utils::VerticalDirection::V_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveIntakeAngle::Interrupted()
{
	End();
}
