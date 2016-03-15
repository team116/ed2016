#include "LiftIntake.h"
#include <Subsystems/Intake.h>

LiftIntake::LiftIntake(Utils::VerticalDirection dir)
{
	Requires(&*intake);

	direction = dir;
}

// Called just before this Command runs the first time
void LiftIntake::Initialize()
{
	intake->setIntakeAngleDirection(direction);

	switch (direction)
	{
	case Utils::VerticalDirection::DOWN:
		log->write(Log::TRACE_LEVEL, "LiftIntake initialized (direction DOWN)");
		break;
	case Utils::VerticalDirection::UP:
		log->write(Log::TRACE_LEVEL, "LiftIntake initialized (direction UP)");
		break;
	case Utils::VerticalDirection::V_STILL:
		log->write(Log::TRACE_LEVEL, "LiftIntake initialized (direction V_STILL)");
		break;
	default:
		log->write(Log::WARNING_LEVEL, "LiftIntake initialized with unknown direction");
		break;
	}
}

// Called repeatedly when this Command is scheduled to run
void LiftIntake::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LiftIntake::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void LiftIntake::End()
{
	intake->setIntakeAngleDirection(Utils::VerticalDirection::V_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftIntake::Interrupted()
{
	End();
}