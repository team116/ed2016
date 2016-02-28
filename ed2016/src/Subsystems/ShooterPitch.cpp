#include "ShooterPitch.h"
#include "../RobotMap.h"
#include <CommandBase.h>
#include <Math.h>

const float ShooterPitch::TARGET_HEIGHT = 246.38;//Centimeters

ShooterPitch::ShooterPitch() :
		Subsystem("ShooterPitch")
{
	pitch_angle = Utils::constructMotor(RobotPorts::SHOOTER_PITCH_MOTOR);
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
		if (CommandBase::sensors->isShooterHomeSwitchHorizontal() )
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
	if (CommandBase::sensors->isShooterHomeSwitchHorizontal())
	{
		pitch_angle->Set(0.0);
	}
}

//In degrees
float ShooterPitch::getPitchToTarget(PitchType type)
{
	switch (type) {
	case PitchType::CAMERA:
		return CommandBase::cameras->PitchFromHorizontal();
		break;
	case PitchType::LIDAR:
		return atan(TARGET_HEIGHT / CommandBase::sensors->lidarDistance());
		break;
	default:
		CommandBase::log->write(Log::WARNING_LEVEL, "Somehow you managed to have an invalid PitchType: %d", type);
		return atan(TARGET_HEIGHT / CommandBase::sensors->lidarDistance());
		break;
	}
}
