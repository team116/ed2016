#include "HolderWheel.h"
#include "../RobotMap.h"

HolderWheel* HolderWheel::INSTANCE = nullptr;

HolderWheel::HolderWheel() : Subsystem("HolderWheel")
{
	holder_wheel = new MOTOR_TYPE(RobotPorts::SHOOTER_PUSH_MOTOR);
}

void HolderWheel::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}



HolderWheel* HolderWheel::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new HolderWheel();
	}
	return INSTANCE;
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
