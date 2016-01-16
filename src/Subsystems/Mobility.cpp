#include <Subsystems/Mobility.h>
#include <RobotMap.h>

Mobility* Mobility::INSTANCE = nullptr;

Mobility::Mobility() :
		Subsystem("Mobility")
{

}

void Mobility::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.


Mobility* Mobility::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Mobility();
	}
	return INSTANCE;
}
