#include "IntakeRoller.h"
#include "../RobotMap.h"
#include <RobotMap.h>

const float IntakeRoller::ROLLER_SPEED = 1.0;

IntakeRoller::IntakeRoller() :
		Subsystem("IntakeRoller")
{
	roller = Utils::constructMotor(RobotPorts::INTAKE_ROLLER_MOTOR);

	direction = Utils::HorizontalDirection::H_STILL;
}

void IntakeRoller::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void IntakeRoller::setDirection(Utils::HorizontalDirection dir)
{
	direction = dir;
	switch (dir)
	{
	case Utils::HorizontalDirection::IN:
		roller->Set(ROLLER_SPEED);
		break;
	case Utils::HorizontalDirection::OUT:
		roller->Set(-ROLLER_SPEED);
		break;
	case Utils::HorizontalDirection::H_STILL:
		roller->Set(0.0);
		break;
	}
}
