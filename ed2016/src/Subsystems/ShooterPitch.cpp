#include "ShooterPitch.h"
#include "../RobotMap.h"
#include <CommandBase.h>
#include <Commands/MaintainShooterAngle.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Cameras.h>
#include <Log.h>
#define _USE_MATH_DEFINES
#include <math.h>

const int ShooterPitch::ANGLE_PRESET_COUNT = 6;
float* ShooterPitch::ANGLE_PRESETS = new float[ShooterPitch::ANGLE_PRESET_COUNT];/* {
	0.0,
	15.0,
	30.0,
	45.0,
	60.0,
	75.0
};*/

const float ShooterPitch::TARGET_HEIGHT = 246.38;//Centimeters to middle of target
const float ShooterPitch::MANUAL_SPEED = 1.0;
const float ShooterPitch::LIDAR_TO_SHOOTER_DISTANCE = 33.01;

ShooterPitch::ShooterPitch() :
		PIDSubsystem("ShooterPitch", 0.09, 0.0, 0.0, 0.0)
{
	pitch_angle = Utils::constructMotor(RobotPorts::SHOOTER_PITCH_MOTOR);

	for (int i = 0; i < ANGLE_PRESET_COUNT; ++i)
	{
		ANGLE_PRESETS[i] = 15.0 * (float)i;
	}

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

	return CommandBase::sensors->shooterAngle();
}

void ShooterPitch::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	setSpeed(output);
}

void ShooterPitch::InitDefaultCommand()
{
	//SetDefaultCommand(new MaintainShooterAngle());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

//Manual Control (Disable PID first)
void ShooterPitch::setSpeed(float speed)
{
	pitch_angle->Set(speed);
}

//Manual Control (Disabled PID first)
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
//Accounts for gravitational acceleration
float ShooterPitch::getPitchToTarget(PitchType type)
{
	float dis;
	switch (type) {
	case PitchType::CAMERA:
		CommandBase::cameras->RefreshContours();
		dis = CommandBase::cameras->GetDistanceFromTarget();
		break;
	case PitchType::LIDAR:
		dis = CommandBase::sensors->lidarDistance();
		//return  90 - ((atan(TARGET_HEIGHT / (CommandBase::sensors->lidarDistance() + LIDAR_TO_SHOOTER_DISTANCE)) * 180) / M_PI);
		break;
	default:
		CommandBase::log->write(Log::WARNING_LEVEL, "Somehow you managed to have an invalid PitchType: %d", type);
		dis = 600;//Random number, went with 6 meters
		return atan(TARGET_HEIGHT / CommandBase::sensors->lidarDistance());
		break;
	}

	//arctan(2y/x)
	return 90 - (atan(2 * TARGET_HEIGHT / (dis + LIDAR_TO_SHOOTER_DISTANCE)) * 180 / M_PI);
}

float ShooterPitch::getAnglePreset(int index)
{
	if (index >= ANGLE_PRESET_COUNT)
	{
		index = ANGLE_PRESET_COUNT - 1;
	}
	else if (index < 0)
	{
		index = 0;
	}
	return ANGLE_PRESETS[index];
}

bool ShooterPitch::isPIDEnabled()
{
	return GetPIDController()->IsEnabled();
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
