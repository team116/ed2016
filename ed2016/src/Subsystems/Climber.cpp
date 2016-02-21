#include <Subsystems/Climber.h>
#include <RobotMap.h>

const float Climber::WINCH_SPEED = 2.2; //temporary speed
const float Climber::CURRENT_SPIKE_THRESHHOLD = 10.0;	//random guess, no idea what this number is actually supposed to look like

Climber::Climber():Subsystem("Climber")
{
	climber_arm_direction = (ClimberArmDirection::CLIMBER_ARM_STILL);
	climber_armed_motor = new MOTOR_TYPE(RobotPorts::CLIMBER_ARMED_MOTOR);
	front_winch = new MOTOR_TYPE(RobotPorts::WINCH_MOTOR_FRONT);
	back_winch = new MOTOR_TYPE(RobotPorts::WINCH_MOTOR_BACK);

	pdp = new PowerDistributionPanel(RobotPorts::PDP);

	back_winch_direction = WinchDirection::ROBOT_STILL;
	front_winch_direction = WinchDirection::ROBOT_STILL;
}

void Climber::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
Climber::ClimberArmDirection Climber::getDirectionClimber()
{
	return climber_arm_direction;
}
Climber::WinchDirection Climber::getFrontWinchDirection()
{
	return front_winch_direction;
}
Climber::WinchDirection Climber::getBackWinchDirection()
{
	return back_winch_direction;
}
void Climber::setClimber(ClimberArmDirection direction, float speed) //function from .h to .cpp
{
	climber_arm_direction = direction;
	if (direction == ClimberArmDirection::CLIMBER_ARM_UP)
	{
		climber_armed_motor->Set(speed);
	}
	else if (direction == ClimberArmDirection::CLIMBER_ARM_DOWN)
	{
		climber_armed_motor->Set(-speed);
	}
	else
	{
		climber_armed_motor->Set(0.0);
	}
}
void Climber::setFrontWinchDirection(WinchDirection direction)
{
	front_winch_direction = direction;
	if (direction == WinchDirection::ROBOT_PULL_UP)
	{
		setFrontWinchSpeed(WINCH_SPEED);
	}
	else if (direction == WinchDirection::ROBOT_PULL_DOWN)
	{
		setFrontWinchSpeed(-WINCH_SPEED);
	}
	else
	{
		setFrontWinchSpeed(0.0);
	}
}

void Climber::setBackWinchDirection (WinchDirection direction)
{
	back_winch_direction = direction;
	if (direction == WinchDirection::ROBOT_PULL_UP)
	{
		setBackWinchSpeed(WINCH_SPEED);
	}
	else if (direction == WinchDirection::ROBOT_PULL_DOWN)
	{
		setBackWinchSpeed(-WINCH_SPEED);
	}
	else
	{
		setBackWinchSpeed(0.0);
	}
}

void Climber::setFrontWinchSpeed(float speed) {
	front_winch->Set(Utils::boundaryCheck(speed, -1.0, 1.0));
}

void Climber::setBackWinchSpeed(float speed) {
	back_winch->Set(Utils::boundaryCheck(speed, -1.0, 1.0));
}

bool Climber::isWinchCurrentSpiking()
{
	if (pdp->GetCurrent(RobotPorts::WINCH_MOTOR_FRONT) > CURRENT_SPIKE_THRESHHOLD
			&& pdp->GetCurrent(RobotPorts::WINCH_MOTOR_BACK) > CURRENT_SPIKE_THRESHHOLD)
	{
		return true;
	}
	else
		return false;
}
