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
	switch (direction)
	{
	case Utils::HorizontalDirection::IN:
		log->write(Log::TRACE_LEVEL, "MoveHolderWheel initialized (direction IN)");
		break;
	case Utils::HorizontalDirection::OUT:
		log->write(Log::TRACE_LEVEL, "MoveHolderWheel initialized (direction OUT)");
		break;
	case Utils::HorizontalDirection::H_STILL:
		log->write(Log::TRACE_LEVEL, "MoveHolderWheel initialized (direction H_STILL)");
		break;
	default:
		log->write(Log::WARNING_LEVEL, "MoveHolderWheel initialized with unknown direction");
		break;
	}
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
