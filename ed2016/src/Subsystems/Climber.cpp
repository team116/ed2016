#include <Subsystems/Climber.h>
#include <RobotMap.h>

Climber* Climber::INSTANCE = nullptr;

const float Climber::WINCH_SPEED = 2.2; //temporary speed

Climber::Climber():Subsystem("Climber")
{
	climber_armed_motor = new MOTOR_TYPE(Robot::CLIMBER_ARMED_MOTOR);
	climber_direction = (ClimberMechanismDirection::CLIMBER_STILL);
	front_winch = new MOTOR_TYPE(Robot::WINCH_MOTOR_FRONT);
	back_winch = new MOTOR_TYPE(Robot::WINCH_MOTOR_BACK);

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
	return climber_direction;
}
void Climber::setClimber(ClimberMechanismDirection direction) //function from .h to .cpp
{
	climber_direction = direction;
	if (direction == ClimberMechanismDirection::CLIMBER_UP)
	{
		climber_armed_motor->Set(0.5);
	}
	else if (direction == ClimberMechanismDirection::CLIMBER_DOWN)
	{
		climber_armed_motor->Set(-0.5);
	}
	else
	{
		climber_armed_motor->Set(0.0);
	}
}
void Climber::setFrontWinch(FrontWinchPullDirection direction)
{
	front_winch_direction = direction;
	if (direction == FrontWinchPullDirection::ROBOT_PULL_UP)
	{
		front_winch->Set(WINCH_SPEED);
	}
	else if (direction == FrontWinchPullDirection::ROBOT_PULL_DOWN)
	{
		front_winch->Set(WINCH_SPEED);
	}
	else
	{
		front_winch->Set(0.0);
	}
}
void Climber::setBackWinch (BackWinchPullDirection direction)
{
	back_winch_direction = direction;
	if (direction == BackWinchPullDirection::PULL_UP_ROBOT)
	{
		back_winch->Set(WINCH_SPEED);
	}
	else if (direction == BackWinchPullDirection::PULL_DOWN_ROBOT)
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
