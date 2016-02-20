#include "RaiseIntake.h"
#include <Subsystems/Intake.h>
RaiseIntake::RaiseIntake()
{
	Requires(&*intake);
	// Use Requires(&*) here to declare subsystem dependencies
	// eg. Requires(&*chassis);
}

// Called just before this Command runs the first time
void RaiseIntake::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RaiseIntake::Execute()
{
	intake->setIntakeAngleDirection(Intake::IntakeAngleDirection::INTAKE_UP);
}

// Make this return true when this Command no longer needs to run execute()
bool RaiseIntake::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RaiseIntake::End()
{
	intake->setIntakeAngleDirection(Intake::IntakeAngleDirection::INTAKE_STOP);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseIntake::Interrupted()
{
	End();
}
