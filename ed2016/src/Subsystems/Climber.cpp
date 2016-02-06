#include <Subsystems/Climber.h>
#include <RobotMap.h>

Climber* Climber::INSTANCE = nullptr;

const float Climber::WINCH_SPEED = 2.2; //temporary speed

Climber::Climber():Subsystem("Climber")
{
	climber_armed_motor = new MOTOR_TYPE(RobotPorts::CLIMBER_ARMED_MOTOR);
	climber_arm_direction = (ClimberMechanismDirection::CLIMBER_ARM_STILL);
	front_winch = new MOTOR_TYPE(RobotPorts::WINCH_MOTOR_FRONT);
	back_winch = new MOTOR_TYPE(RobotPorts::WINCH_MOTOR_BACK);

	back_winch_direction = WinchPullDirection::ROBOT_STILL;

}

void Climber::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
Climber::ClimberMechanismDirection Climber::getDirectionClimber()
{
	return climber_arm_direction;
}
Climber::WinchPullDirection Climber::getFrontWinchDirection()
{
	return front_winch_direction;
}
Climber::WinchPullDirection Climber::getBackWinchDirection()
{
	return back_winch_direction;
}
void Climber::setClimber(ClimberMechanismDirection direction) //function from .h to .cpp
{
	climber_arm_direction = direction;
	if (direction == ClimberMechanismDirection::CLIMBER_ARM_UP)
	{
		climber_armed_motor->Set(0.5);
	}
	else if (direction == ClimberMechanismDirection::CLIMBER_ARM_DOWN)
	{
		climber_armed_motor->Set(-0.5);
	}
	else
	{
		climber_armed_motor->Set(0.0);
	}
}
void Climber::setFrontWinch(WinchPullDirection direction)
{
	front_winch_direction = direction;
	if (direction == WinchPullDirection::ROBOT_PULL_UP)
	{
		front_winch->Set(WINCH_SPEED);
	}
	else if (direction == WinchPullDirection::ROBOT_PULL_DOWN)
	{
		front_winch->Set(WINCH_SPEED);
	}
	else
	{
		front_winch->Set(0.0);
	}
}
void Climber::setBackWinch (WinchPullDirection direction)
{
	back_winch_direction = direction;
	if (direction == WinchPullDirection::ROBOT_PULL_UP)
	{
		back_winch->Set(WINCH_SPEED);
	}
	else if (direction == WinchPullDirection::ROBOT_PULL_DOWN)
	{
		back_winch->Set(WINCH_SPEED);
	}
	else
	{
		back_winch->Set(0.0);
	}

}

Climber* Climber::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Climber();
	}
	return INSTANCE;
}
