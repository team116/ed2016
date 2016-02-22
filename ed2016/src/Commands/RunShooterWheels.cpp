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

}

// Called repeatedly when this Command is scheduled to run
void RunShooterWheels::Execute()
{
	if(oi->getShooterWheelsSwitch()) {
		shooter->setShooterSpeed(shooter->getSpeedPreset(oi->getShooterSpeedPosition()));
	}
	else {
		shooter->setShooterSpeed(0.0);
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

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunShooterWheels::Interrupted()
{
	End();
}
