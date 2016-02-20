#include "LowerIntake.h"
#include <Subsystems/Intake.h>
LowerIntake::LowerIntake()
{
	// Use Requires(&*) here to declare subsystem dependencies
	// eg. Requires(&*chassis);
}

// Called just before this Command runs the first time
void LowerIntake::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void LowerIntake::Execute()
{
	intake->setIntakeAngleDirection(Intake::IntakeAngleDirection::INTAKE_DOWN);
}

// Make this return true when this Command no longer needs to run execute()
bool LowerIntake::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void LowerIntake::End()
{
	intake->setIntakeAngleDirection(Intake::IntakeAngleDirection::INTAKE_STOP);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerIntake::Interrupted()
{
	End();
}
