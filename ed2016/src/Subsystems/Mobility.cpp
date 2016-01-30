#include <Subsystems/Mobility.h>
#include <RobotMap.h>
#include <Commands/JoystickDrive.h>

Mobility* Mobility::INSTANCE = nullptr;

Mobility::Mobility() : Subsystem("Mobility")
{
	leftFront = new CANTalon(Robot::LEFT_FRONT_MOTOR);
	leftBack = new CANTalon(Robot::LEFT_BACK_MOTOR);
	rightFront = new CANTalon(Robot::RIGHT_FRONT_MOTOR);
	rightBack = new CANTalon(Robot::RIGHT_BACK_MOTOR);

	leftFront->EnableControl();
	leftBack->EnableControl();
	rightFront->EnableControl();
	rightBack->EnableControl();

	front_orientation = true; // just to get rid of uninitialized warning
	useFrontOrientation(true); // this is the actual initializer
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

void Mobility::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new JoystickDrive());
}

void Mobility::setStraight(float speed)
{
	setLeft(speed);
	setRight(speed);
}

void Mobility::setLeft(float speed)
{
	if (front_orientation)
	{
		leftFront->Set(speed);
		leftBack->Set(speed);
	}
	else
	{
		leftFront->Set(-speed);
		leftBack->Set(-speed);
	}
}

void Mobility::setRight(float speed)
{
	if (front_orientation)
	{
		rightFront->Set(-speed);
		rightBack->Set(-speed);
	}
	else
	{
		rightFront->Set(speed);
		rightBack->Set(speed);
	}
}

void Mobility::useFrontOrientation(bool front)
{
	front_orientation = front;
}

Mobility* Mobility::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Mobility();
	}
	return INSTANCE;
}
