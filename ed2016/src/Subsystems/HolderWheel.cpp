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

void HolderWheel::turnHolderWheelOn(bool turningOn)
{
	if(turningOn)
	{
		holder_wheel->Set(1.0);
	}
	else
	{
		holder_wheel->Set(0.0);
	}
}

HolderWheel* HolderWheel::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new HolderWheel();
	}
	return INSTANCE;
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
