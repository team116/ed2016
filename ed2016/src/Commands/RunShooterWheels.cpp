#include <Commands/RunShooterWheels.h>
#include <OI.h>
#include <Subsystems/ShooterPID.h>

RunShooterWheels::RunShooterWheels()
{
	Requires(&*shooter);
}

// Called just before this Command runs the first time
void RunShooterWheels::Initialize()
{
	log->write(Log::TRACE_LEVEL, "RunShooterWheels Initialized");
}

// Called repeatedly when this Command is scheduled to run
void RunShooterWheels::Execute()
{
	if(oi->getShooterWheelsSwitch()) {
		shooter->Enable();
		shooter->SetSetpoint(shooter->getRPMPreset(oi->getShooterSpeedPosition()));
	}
	else {
		shooter->SetSetpoint(0);
		shooter->Disable();
		shooter->setShooterSpeed(0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RunShooterWheels::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RunShooterWheels::End()
{
	log->write(Log::TRACE_LEVEL, "RunShooterWheels Ended");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunShooterWheels::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "RunShooterWheels Interrupted");
	End();
}
