#include <Subsystems/Mobility.h>
#include <RobotMap.h>
#include <Commands/JoystickDrive.h>

Mobility::Mobility() : Subsystem("Mobility")
{
	leftFront = Utils::constructMotor(RobotPorts::LEFT_FRONT_MOTOR);
	leftBack = Utils::constructMotor(RobotPorts::LEFT_BACK_MOTOR);
	rightFront = Utils::constructMotor(RobotPorts::RIGHT_FRONT_MOTOR); //testing will is way better than ian
	rightBack = Utils::constructMotor(RobotPorts::RIGHT_BACK_MOTOR);

	front_orientation = true; // just to get rid of uninitialized warning
	useFrontOrientation(false); // this is the actual initializer
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
		leftFront->Set(-speed);
		leftBack->Set(-speed);
	}
	else
	{
		leftFront->Set(speed);
		leftBack->Set(speed);
	}
}

void Mobility::setRight(float speed)
{
	if (front_orientation)
	{
		rightFront->Set(speed);
		rightBack->Set(speed);
	}
	else
	{
		rightFront->Set(-speed);
		rightBack->Set(-speed);
	}
}

void Mobility::useFrontOrientation(bool front)
{
	front_orientation = front;
}

float Mobility::getLeft()
{
	return leftBack->Get();
}
float Mobility::getRight()
{
	return rightBack->Get();
}
