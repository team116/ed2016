#include <CheckManualOverrides.h>
#include <Commands/RunShooterWheels.h>
#include <OI.h>
#include <Subsystems/Shooter.h>

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
	if(!DriverStation::GetInstance().IsAutonomous())
	{
		if(oi->getShooterWheelsSwitch())
		{
			shooter->setRPM(shooter->getRPMPreset(oi->getShooterSpeedPosition()));
		}
		else
		{
			shooter->setRPM(0.0);
			shooter->setSpeed(0.0);
		}
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
