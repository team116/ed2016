#include "IntakeOut.h"
#include <Subsystems/Intake.h>

IntakeOut::IntakeOut()
{
	Requires (&*intake);
	// Use Requires(&*) here to declare subsystem dependencies
	// eg. Requires(&*chassis);
}

// Called just before this Command runs the first time
void IntakeOut::Initialize()
{
	DriverStation::ReportError("Out init\n");
}

// Called repeatedly when this Command is scheduled to run
void IntakeOut::Execute()
{
	intake->setIntakeDirection(Intake::IntakeDirection::INTAKE_OUT);
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeOut::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void IntakeOut::End()
{
	DriverStation::ReportError("Out end\n");
	intake->setIntakeDirection(Intake::IntakeDirection::INTAKE_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeOut::Interrupted()
{
	End();
}
