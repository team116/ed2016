#include <Subsystems/Climber.h>
#include <RobotMap.h>

Climber* Climber::INSTANCE = nullptr;

Climber::Climber() :
		Subsystem("Climber")
{

}

void Climber::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

Climber* Climber::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Climber();
	}
	return INSTANCE;
}
