#include <Commands/MoveIntake.h>
#include <CommandBase.h>


MoveIntake::MoveIntake(Intake::IntakeDirection direction)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires (&*intake);

	 this->direction = direction;
}

// Called just before this Command runs the first time
void MoveIntake::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void MoveIntake::Execute()
{
	CommandBase::intake->setIntakeDirection(direction);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveIntake::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MoveIntake::End()
{
	CommandBase::intake->setIntakeDirection(Intake::INTAKE_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveIntake::Interrupted()
{
	End();
}
