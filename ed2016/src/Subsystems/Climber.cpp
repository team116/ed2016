#include <Subsystems/Climber.h>
#include <RobotMap.h>
#include <Log.h>

const float Climber::WINCH_SPEED = 2.2; //temporary speed
const float Climber::WINCH_CURRENT_SPIKE_THRESHHOLD = 10.0;	//random guess, no idea what this number is actually supposed to look like
const float Climber::CLIMBER_CURRENT_SPIKE_THRESHHOLD = 10.0; //Ditto

Climber::Climber():Subsystem("Climber")
{
	climber_arm_direction = Utils::VerticalDirection::V_STILL;
	climber_armed_motor = Utils::constructMotor(RobotPorts::CLIMBER_ARMED_MOTOR);
	front_winch = Utils::constructMotor(RobotPorts::WINCH_MOTOR_FRONT);
	back_winch = Utils::constructMotor(RobotPorts::WINCH_MOTOR_BACK);

	pdp = new PowerDistributionPanel(RobotPorts::PDP);

	back_winch_direction = Utils::VerticalDirection::V_STILL;
	front_winch_direction = Utils::VerticalDirection::V_STILL;
}

void Climber::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
Utils::VerticalDirection Climber::getDirectionClimber()
{
	return climber_arm_direction;
}
Utils::VerticalDirection Climber::getFrontWinchDirection()
{
	return front_winch_direction;
}
Utils::VerticalDirection Climber::getBackWinchDirection()
{
	return back_winch_direction;
}
void Climber::setClimber(Utils::VerticalDirection direction, float speed) //function from .h to .cpp
{
	climber_arm_direction = direction;
	if (direction == Utils::VerticalDirection::UP)
	{
		climber_armed_motor->Set(speed);
	}
	else if (direction == Utils::VerticalDirection::DOWN)
	{
		climber_armed_motor->Set(-speed);
	}
	else
	{
		climber_armed_motor->Set(0.0);
	}
}
void Climber::setFrontWinchDirection(Utils::VerticalDirection direction)
{
	front_winch_direction = direction;
	if (direction == Utils::VerticalDirection::UP)
	{
		setFrontWinchSpeed(WINCH_SPEED);
	}
	else if (direction == Utils::VerticalDirection::DOWN)
	{
		setFrontWinchSpeed(-WINCH_SPEED);
	}
	else
	{
		setFrontWinchSpeed(0.0);
	}
}

void Climber::setBackWinchDirection (Utils::VerticalDirection direction)
{
	back_winch_direction = direction;
	if (direction == Utils::VerticalDirection::UP)
	{
		setBackWinchSpeed(WINCH_SPEED);
	}
	else if (direction == Utils::VerticalDirection::DOWN)
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
	Log::getInstance()->write(Log::INFO_LEVEL, "Current Winch Current Front: %f Back: %f", pdp->GetCurrent(RobotPorts::WINCH_MOTOR_FRONT),
			pdp->GetCurrent(RobotPorts::WINCH_MOTOR_BACK));
	if (pdp->GetCurrent(RobotPorts::WINCH_MOTOR_FRONT) > WINCH_CURRENT_SPIKE_THRESHHOLD
			&& pdp->GetCurrent(RobotPorts::WINCH_MOTOR_BACK) > WINCH_CURRENT_SPIKE_THRESHHOLD)
	{
		return true;
	}
	else
		return false;
}

bool Climber::isClimberCurrentSpiking()
{
	Log::getInstance()->write(Log::INFO_LEVEL, "Current Climber Current"
			": %f", pdp->GetCurrent(RobotPorts::CLIMBER_ARMED_MOTOR));
	if(pdp->GetCurrent(RobotPorts::CLIMBER_ARMED_MOTOR) > CLIMBER_CURRENT_SPIKE_THRESHHOLD) {
		return true;
	}
	else {
		return false;
	}
}
