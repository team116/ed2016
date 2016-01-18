#include <Subsystems/Mobility.h>
#include <RobotMap.h>

Mobility* Mobility::INSTANCE = nullptr;

Mobility::Mobility() : Subsystem("ExampleSubsystem")
{
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

void Mobility::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}
void Mobility::SetLeft(float motor1){

}

void Mobility::SetRight(float motor2){

}

Mobility* Mobility::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Mobility();
	}
	return INSTANCE;
}
