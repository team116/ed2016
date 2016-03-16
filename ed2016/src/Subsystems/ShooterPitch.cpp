#include "ShooterPitch.h"
#include "../RobotMap.h"
#include <CommandBase.h>
#include <Commands/MaintainShooterAngle.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Cameras.h>
#include <Log.h>
#define _USE_MATH_DEFINES
#include <math.h>

const float ShooterPitch::TARGET_HEIGHT = 185.42;//Centimeters to middle of target
const float ShooterPitch::MANUAL_SPEED = 1.0;
const float ShooterPitch::LIDAR_TO_SHOOTER_DISTANCE = 33.01;

ShooterPitch::ShooterPitch() :
		PIDSubsystem("ShooterPitch", 0.09, 0.0, 0.0, 0.0)
{
	pitch_angle = Utils::constructMotor(RobotPorts::SHOOTER_PITCH_MOTOR);

	SetInputRange(-90, 270);
	SetAbsoluteTolerance(0.0);
	SetOutputRange(-1.0,1.0);

	GetPIDController()->SetContinuous(false);
}

double ShooterPitch::ReturnPIDInput()
{
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;

	CommandBase::log->write(Log::INFO_LEVEL, "PID Input: %f", CommandBase::sensors->shooterAngle());
	return CommandBase::sensors->shooterAngle();
}

void ShooterPitch::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	CommandBase::log->write(Log::INFO_LEVEL, "PID Output: %f", output);
	setSpeed(output);
}

void ShooterPitch::InitDefaultCommand()
{
	//SetDefaultCommand(new MaintainShooterAngle());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void ShooterPitch::setSpeed(float speed)
{
	pitch_angle->Set(speed);
}

void ShooterPitch::setDirection(Utils::VerticalDirection dir)
{
	//Note: 1.0 and -1.0 may need to be reversed
	if(dir == Utils::VerticalDirection::UP)
	{
		setSpeed(MANUAL_SPEED);
	}
	else if (dir == Utils::VerticalDirection::DOWN){
		if (CommandBase::sensors->isShooterHomeSwitchHorizontal() )
		{
			setSpeed(0.0);
		}
		else
		{
			setSpeed(-MANUAL_SPEED);
		}
	}
	else
	{
		setSpeed(0.0);
	}
}

void ShooterPitch::checkLimits()
{
	if(CommandBase::sensors->isShooterHomeSwitchHorizontal()) {
		CommandBase::sensors->zeroShooterPitch();
	}
}

//In degrees
float ShooterPitch::getTargetPitch(PitchType type)
{
	switch (type) {
	case PitchType::CAMERA:
		return CommandBase::cameras->PitchFromHorizontal();
		break;
	case PitchType::LIDAR:
		return  90 - ((atan(TARGET_HEIGHT / (CommandBase::sensors->lidarDistance() + LIDAR_TO_SHOOTER_DISTANCE)) * 180) / M_PI);
		break;
	default:
		CommandBase::log->write(Log::WARNING_LEVEL, "Somehow you managed to have an invalid PitchType: %d", type);
		return atan(TARGET_HEIGHT / CommandBase::sensors->lidarDistance());
		break;
	}
}

float ShooterPitch::getP()
{
	return GetPIDController()->GetP();
}
float ShooterPitch::getI()
{
	return GetPIDController()->GetI();
}
float ShooterPitch::getD()
{
	return GetPIDController()->GetD();
}
float ShooterPitch::getF()
{
	return GetPIDController()->GetF();
}

void ShooterPitch::setP(float p)
{
	GetPIDController()->SetPID(p, getI(), getD());
}
void ShooterPitch::setI(float i)
{
	GetPIDController()->SetPID(getP(), i, getD());
}
void ShooterPitch::setD(float d)
{
	GetPIDController()->SetPID(getP(), getI(), d);
}
void ShooterPitch::setF(float f)
{
	GetPIDController()->SetPID(getP(), getI(), getD(), f);
}
