#include <Subsystems/Shooter.h>
#include <RobotMap.h>

Shooter* Shooter::INSTANCE = nullptr;

Shooter::Shooter() :
		Subsystem("Shooter")
{

}

void Shooter::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

Shooter* Shooter::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Shooter();
	}
	return INSTANCE;
}
