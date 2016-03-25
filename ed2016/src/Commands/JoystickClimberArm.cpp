#include "JoystickClimberArm.h"
#include <Subsystems/Climber.h>
#include <OI.h>

JoystickClimberArm::JoystickClimberArm()
{
	Requires(&*climber);
}

// Called just before this Command runs the first time
void JoystickClimberArm::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void JoystickClimberArm::Execute()
{
	float speed = oi->getFrontWinchY();
	if (speed < 0.0)
	{
		climber->setClimber(Utils::VerticalDirection::DOWN, -speed);
	}
	else if (speed > 0.0)
	{
		climber->setClimber(Utils::VerticalDirection::UP, speed);
	}
	else
	{
		climber->setClimber(Utils::VerticalDirection::V_STILL, 0.0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickClimberArm::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void JoystickClimberArm::End()
{
	climber->setClimber(Utils::VerticalDirection::V_STILL, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickClimberArm::Interrupted()
{
	End();
}
