#include <Commands/MoveHolderWheel.h>
#include <Subsystems/HolderWheel.h>

MoveHolderWheel::MoveHolderWheel(Utils::HorizontalDirection dir)
{
	Requires(&*holder_wheel);
	direction = dir;
}

// Called just before this Command runs the first time
void MoveHolderWheel::Initialize()
{
	holder_wheel->setWheelDirection(direction);
}

// Called repeatedly when this Command is scheduled to run
void MoveHolderWheel::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool MoveHolderWheel::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MoveHolderWheel::End()
{
	holder_wheel->setWheelDirection(Utils::HorizontalDirection::H_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveHolderWheel::Interrupted()
{
	End();
}
