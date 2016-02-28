#include <Commands/MoveBackWinch.h>
#include <RobotMap.h>
#include <Subsystems/Climber.h>

MoveBackWinch::MoveBackWinch(Utils::VerticalDirection dir)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(&*climber);

	movement_direction = dir;
}

// Called just before this Command runs the first time
void MoveBackWinch::Initialize()
{
	log->write(Log::TRACE_LEVEL, "MoveBackWinch Initialized");
	climber->setBackWinchDirection(movement_direction);
}

// Called repeatedly when this Command is scheduled to run
void MoveBackWinch::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool MoveBackWinch::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MoveBackWinch::End()
{
	log->write(Log::TRACE_LEVEL, "MoveBackWinch Ended");
	climber->setBackWinchDirection(Utils::VerticalDirection::V_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveBackWinch::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "MoveBackWinch Interrupted");
	End();
}
