#include "MoveClimberArm.h"
#include <Subsystems/Climber.h>

MoveClimberArm::MoveClimberArm(Utils::VerticalDirection dir)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(&*climber);

	movement_direction = dir;
}

// Called just before this Command runs the first time
void MoveClimberArm::Initialize()
{
	log->write(Log::TRACE_LEVEL, "MoveClimberArm Initialized");

	switch (movement_direction)
	{
	case Utils::VerticalDirection::UP:
		climber->setClimber(movement_direction, Climber::DEPLOY_ARM_SPEED);
		break;
	case Utils::VerticalDirection::DOWN:
		climber->setClimber(movement_direction, Climber::RETRACT_ARM_SPEED);
		break;
	case Utils::VerticalDirection::V_STILL:
		climber->setClimber(movement_direction);
		break;
	}
}

// Called repeatedly when this Command is scheduled to run
void MoveClimberArm::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool MoveClimberArm::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MoveClimberArm::End()
{
	log->write(Log::TRACE_LEVEL, "MoveClimberArm Ended");
	climber->setClimber(Utils::VerticalDirection::V_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveClimberArm::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "MoveClimberArm Interrupted");
	End();
}
