#include <Commands/ClearCommands.h>
#include <Subsystems/Climber.h>
#include <Subsystems/HolderWheel.h>
#include <Subsystems/Intake.h>
#include <Subsystems/Mobility.h>
#include <Subsystems/ShooterPID.h>

ClearCommands::ClearCommands()
{
	// Use Requires(&*) here to declare subsystem dependencies
	// eg. Requires(&*chassis);
	Requires(&*mobility);
	Requires(&*shooter);
	Requires(&*climber);
	Requires(&*intake);
	Requires(&*holder_wheel);
}

// Called just before this Command runs the first time
void ClearCommands::Initialize()
{
	log->write(Log::TRACE_LEVEL, "Clear Commands Initialized");

}

// Called repeatedly when this Command is scheduled to run
void ClearCommands::Execute()
{
	Scheduler::GetInstance()->RemoveAll();
}

// Make this return true when this Command no longer needs to run execute()
bool ClearCommands::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ClearCommands::End()
{
	log->write(Log::TRACE_LEVEL, "Clear Commands Ended");

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClearCommands::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "Clear Commands Interrupted");

}
