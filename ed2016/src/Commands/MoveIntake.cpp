#include <Commands/MoveIntake.h>
#include <CommandBase.h>


MoveIntake::MoveIntake(Utils::HorizontalDirection direction)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires (&*intake);

	 this->direction = direction;
}

// Called just before this Command runs the first time
void MoveIntake::Initialize()
{
	log->write(Log::TRACE_LEVEL, "MoveIntake Initialized");
	intake->setIntakeDirection(direction);
	holder_wheel->setWheelDirection(direction);
}

// Called repeatedly when this Command is scheduled to run
void MoveIntake::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool MoveIntake::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MoveIntake::End()
{
	log->write(Log::TRACE_LEVEL, "MoveIntake Ended");
	CommandBase::intake->setIntakeDirection(Utils::HorizontalDirection::H_STILL);
	CommandBase::holder_wheel->setWheelDirection(Utils::HorizontalDirection::H_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveIntake::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "MoveIntake Interrupted");
	End();
}
