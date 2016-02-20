#include "IntakeIn.h"
#include <Subsystems/Intake.h>

IntakeIn::IntakeIn()
{
	Requires(&*intake);
	// Use Requires(&*) here to declare subsystem dependencies
	// eg. Requires(&*chassis);
}

// Called just before this Command runs the first time
void IntakeIn::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void IntakeIn::Execute()
{
	intake->setIntakeDirection(Intake::IntakeDirection::INTAKE_IN);
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeIn::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void IntakeIn::End()
{
	intake->setIntakeDirection(Intake::IntakeDirection::INTAKE_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeIn::Interrupted()
{
	End();
}
