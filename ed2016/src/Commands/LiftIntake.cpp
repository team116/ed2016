#include <CheckManualOverrides.h>
#include "LiftIntake.h"
#include <Subsystems/Intake.h>
#include <Subsystems/Sensors.h>

LiftIntake::LiftIntake(Utils::VerticalDirection dir)
{
	Requires(&*intake);

	pid_enabled = false;
	direction = dir;
}

// Called just before this Command runs the first time
void LiftIntake::Initialize()
{
	pid_enabled = intake->isPIDEnabled();
	if (pid_enabled)
	{
		// prevent PID from fighting the manual controls
		CheckManualOverrides::requestPIDEnable(&*intake, false);
//		intake->Disable();
	}

	intake->setIntakeAngleDirection(direction);

	switch (direction)
	{
	case Utils::VerticalDirection::DOWN:
		log->write(Log::TRACE_LEVEL, "LiftIntake initialized (direction DOWN, pid %d)", pid_enabled);
		break;
	case Utils::VerticalDirection::UP:
		log->write(Log::TRACE_LEVEL, "LiftIntake initialized (direction UP, pid %d)", pid_enabled);
		break;
	case Utils::VerticalDirection::V_STILL:
		log->write(Log::TRACE_LEVEL, "LiftIntake initialized (direction V_STILL, pid %d)", pid_enabled);
		break;
	default:
		log->write(Log::WARNING_LEVEL, "LiftIntake initialized with unknown direction, pid %d", pid_enabled);
		break;
	}
}

// Called repeatedly when this Command is scheduled to run
void LiftIntake::Execute()
{
	intake->setIntakeAngleDirection(direction);
}

// Make this return true when this Command no longer needs to run execute()
bool LiftIntake::IsFinished()
{
	return direction == Utils::VerticalDirection::V_STILL && !intake->isPIDEnabled();
}

// Called once after isFinished returns true
void LiftIntake::End()
{
	log->write(Log::TRACE_LEVEL, "LiftIntake ended w/ direction %d", (int)direction);
	if (pid_enabled)
	{
		CheckManualOverrides::requestPIDEnable(&*intake, true);
		// intake->Enable();
		intake->SetSetpoint(sensors->intakeAngle());
	}
	else
	{
		intake->setIntakeAngleDirection(Utils::VerticalDirection::V_STILL);
	}
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftIntake::Interrupted()
{
	End();
}
