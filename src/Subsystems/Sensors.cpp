#include <Subsystems/Sensors.h>
#include <RobotMap.h>

Sensors* Sensors::INSTANCE = nullptr;
Sensors::Sensors() : Subsystem("Sensors")
{

}

void Sensors::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
bool Sensors::isLimitSwitched()
{
	return false;
}

float Sensors::shooterAngle()
{
	return 0.0;
}
Sensors* Sensors::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Sensors();
	}
	return INSTANCE;
}
