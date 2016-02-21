#include "HolderWheel.h"
#include "../RobotMap.h"

HolderWheel::HolderWheel() : Subsystem("HolderWheel")
{
	holder_wheel = Utils::constructMotor(RobotPorts::SHOOTER_PUSH_MOTOR);
}

void HolderWheel::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void HolderWheel::holderWheelDirection(HolderWheelDirection direction)
{
	if (direction == WHEEL_IN)
	{
		holder_wheel->Set(1.0);
	}
	else if (direction == WHEEL_OUT)
	{
		holder_wheel->Set(-1.0);
	}
	else
	{
		holder_wheel->Set(0.0);
	}
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
