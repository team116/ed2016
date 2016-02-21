#include <Commands/MoveIntake.h>

MoveIntake::MoveIntake(Intake::IntakeDirection direction)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires (&*intake);
}

// Called just before this Command runs the first time
void MoveIntake::Initialize()
{

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

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveIntake::Interrupted()
{

}
