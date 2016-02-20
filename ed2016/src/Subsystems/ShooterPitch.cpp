#include "ShooterPitch.h"
#include "../RobotMap.h"
#include <Subsystems/Sensors.h>

ShooterPitch* ShooterPitch::INSTANCE = nullptr;

ShooterPitch::ShooterPitch() :
		Subsystem("ShooterPitch")
{
	pitch_angle = new MOTOR_TYPE(RobotPorts::SHOOTER_PITCH_MOTOR);
}

void ShooterPitch::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void ShooterPitch::setShooterPitchDirection(ShooterPitchDirection dir)
{
	//Note: 1.0 and -1.0 may need to be reversed
	if(dir == SHOOTER_UP)
	{
		pitch_angle->Set(1.0);
	}
	else if (dir == SHOOTER_DOWN){
		if (sensors->isShooterHomeSwitchHorizontal() )
			{
			pitch_angle->Set(0.0);
			}
		else
		{
			pitch_angle->Set(-1.0);
		}
	}
	else
	{
		pitch_angle->Set(0.0);
	}
}

void ShooterPitch::checkLimits()
{
	if (sensors->isShooterHomeSwitchHorizontal())
	{
		pitch_angle->Set(0.0);
	}
}

ShooterPitch* ShooterPitch::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new ShooterPitch();
	}
	return INSTANCE;
}
