#include "HolderWheel.h"
#include "../RobotMap.h"

HolderWheel::HolderWheel() : Subsystem("HolderWheel")
{
	holder_wheel = Utils::constructMotor(RobotPorts::SHOOTER_PUSH_MOTOR);

	wheel_direction = Utils::H_STILL;
}

void HolderWheel::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void HolderWheel::setWheelDirection(Utils::HorizontalDirection direction)
{
	wheel_direction = direction;
	if (direction == Utils::HorizontalDirection::IN)
	{
		holder_wheel->Set(-1.0);
	}
	else if (direction == Utils::HorizontalDirection::OUT)
	{
		holder_wheel->Set(1.0);
	}
	else
	{
		holder_wheel->Set(0.0);
	}
}

Utils::HorizontalDirection HolderWheel::getWheelDirection()
{
	return wheel_direction;
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
