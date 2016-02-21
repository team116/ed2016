#include <Commands/IntakeOut.h>
#include <Subsystems/Intake.h>
#include <Commands/MoveIntake.h>
#include <CommandBase.h>

IntakeOut::IntakeOut(Intake::IntakeDirection direction)
{
	Requires (&*intake);
	// Use Requires(&*) here to declare subsystem dependencies
	// eg. Requires(&*chassis);

	this->direction = direction;
}

// Called just before this Command runs the first time
void IntakeOut::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void IntakeOut::Execute()
{
	CommandBase::intake->setIntakeDirection(direction);
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeOut::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void IntakeOut::End()
{
	CommandBase::intake->setIntakeDirection(Intake::INTAKE_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeOut::Interrupted()
{
	End();
}
