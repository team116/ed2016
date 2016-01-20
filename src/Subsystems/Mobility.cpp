#include <Subsystems/Mobility.h>
#include <RobotMap.h>
#include <Commands/JoystickDrive.h>

Mobility* Mobility::INSTANCE = nullptr;

Mobility::Mobility() : Subsystem("Mobility")
{
	leftFront = new CANTalon(1);
	leftBack = new CANTalon(2);
	rightFront = new CANTalon(3);
	rightBack = new CANTalon(4);

	leftFront->EnableControl();
	leftBack->EnableControl();
	rightFront->EnableControl();
	rightBack->EnableControl();


}
// Put methods for controlling this subsystem
// here. Call these from Commands.

void Mobility::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());

}
void Mobility::SetLeft(float speed){

	leftFront->Set(speed);
	leftBack->Set(speed);

}

void Mobility::SetRight(float speed){
	rightFront->Set(speed);
	rightBack->Set(speed);

}

Mobility* Mobility::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Mobility();
	}
	return INSTANCE;
}
