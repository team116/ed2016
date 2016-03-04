#include "TogglePID.h"

TogglePID::TogglePID(bool state)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);

	use_pid = state;
	finished = false;
}

// Called just before this Command runs the first time
void TogglePID::Initialize()
{
	CommandBase::log->write(Log::TRACE_LEVEL, "TogglePID initializing (PID State: %d)", use_pid);
	finished = false;
	if(use_pid) {
		shooter_pitch->Enable();
	}
	else {
		shooter_pitch->Disable();
	}
	finished = true;
}

// Called repeatedly when this Command is scheduled to run
void TogglePID::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool TogglePID::IsFinished()
{
	return finished;
}

// Called once after isFinished returns true
void TogglePID::End()
{
	CommandBase::log->write(Log::TRACE_LEVEL, "TogglePID ended");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TogglePID::Interrupted()
{
	CommandBase::log->write(Log::TRACE_LEVEL, "TogglePID interrupted");
	End();
}
