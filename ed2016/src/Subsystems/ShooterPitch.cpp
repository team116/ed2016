#include "ShooterPitch.h"
#include "../RobotMap.h"
#include <CommandBase.h>
#include <Commands/MaintainShooterAngle.h>
#include <Commands/SetShooterPitch.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Cameras.h>
#include <Log.h>
#define _USE_MATH_DEFINES
#include <math.h>

const int ShooterPitch::ANGLE_PRESET_COUNT = 6;

const float ShooterPitch::ZERO_ANGLE_ZONE = 3.0;

float* ShooterPitch::ANGLE_PRESETS = new float[ShooterPitch::ANGLE_PRESET_COUNT];/* {
	0.0,
	15.0,
	30.0,
	45.0,
	60.0,
	75.0
};*/

const float ShooterPitch::SHOOTER_HEIGHT = 45.72;//cm
const float ShooterPitch::SHOOTER_TO_TARGET_HEIGHT = (Cameras::TARGET_ELEVATION - SHOOTER_HEIGHT) / 100.0;//METERS
const float ShooterPitch::MANUAL_SPEED = 1.0;
const float ShooterPitch::LIDAR_TO_SHOOTER_DISTANCE = 27.04;//cm

ShooterPitch::ShooterPitch() :
		PIDSubsystem("ShooterPitch", 0.1, 0.0001, 0.0, 0.0)
{
	pitch_angle = Utils::constructMotor(RobotPorts::SHOOTER_PITCH_MOTOR);
	move_shooter_to_zero = new MoveShooterToZero();

	for (int i = 0; i < ANGLE_PRESET_COUNT; ++i)
	{
		ANGLE_PRESETS[i] = 15.0 * (float)i;
	}

	SetInputRange(-90, 270);
	SetAbsoluteTolerance(0.5);
	SetOutputRange(-1.0,1.0);

	GetPIDController()->SetContinuous(false);
}

double ShooterPitch::ReturnPIDInput()
{
//	if (!CommandBase::sensors->isShooterAngleEnabled())
//	{
//		Disable();
//	}
	return CommandBase::sensors->shooterAngle();
}

void ShooterPitch::UsePIDOutput(double output)
{
	setSpeed(output);
}

void ShooterPitch::InitDefaultCommand()
{
	//SetDefaultCommand(new MaintainShooterAngle());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void ShooterPitch::setAngle(float degrees)
{
	if (degrees < ZERO_ANGLE_ZONE && !move_shooter_to_zero->IsRunning())
	{
		Scheduler::GetInstance()->AddCommand(move_shooter_to_zero);
	}
	else
	{
		if (move_shooter_to_zero->IsRunning())
		{
			move_shooter_to_zero->Cancel();
		}
		SetSetpoint(degrees);
	}
}

//Manual Control (Disable PID first)
void ShooterPitch::setSpeed(float speed)
{
	if (speed < 0.0 && CommandBase::sensors->isShooterHomeSwitchHorizontal())
	{
		pitch_angle->Set(0.0);
	}
	else
	{
		pitch_angle->Set(speed);
	}
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
		setSpeed(-MANUAL_SPEED);
	}
	else
	{
		setSpeed(0.0);
	}
}

void ShooterPitch::checkLimits()
{
	if(CommandBase::sensors->isShooterHomeSwitchHorizontal())
	{
		CommandBase::sensors->zeroShooterPitch();
		SetShooterPitch::zeroTimedAngleTracker();

		if (getSpeed() < 0.0)
		{
			setSpeed(0.0);
		}
	}
}

//In degrees
//Accounts for gravitational acceleration
float ShooterPitch::getPitchToTarget(float dis, float velocity)//Distance in cm Velocity in m/s
{
	dis /= 100.0;

	//CommandBase::log->write(Log::DEBUG_LEVEL, "Distance: %f", dis);

	float angle;

	//arctan((v^2 - sqr(v^4 - g(gx^2 + 2yv^2))) / (gx))
	float radicand = pow(velocity, 4) - 9.8 * (9.8 * pow(dis, 2) + 2 * SHOOTER_TO_TARGET_HEIGHT * pow(velocity, 2));
	if(radicand >= 0) {
		float numerator = pow(velocity, 2) - sqrt(radicand);
		float denominator = 9.8 * dis;
		angle = atan(numerator /  denominator);

		//CommandBase::log->write(Log::DEBUG_LEVEL, "Radicand: %f Numerator: %f Denominator: %f Angle: %f", radicand, numerator, denominator, angle);
	}
	else {
		CommandBase::log->write(Log::WARNING_LEVEL, "Warning: Non-real angle (Radicand: %f Distance: %f Velocity: %f)", radicand, dis, velocity);
		return -1;
	}

	//arctan(2y/x)
	//angle =  90 - (atan(2 * TARGET_HEIGHT / (dis)) * 180 / M_PI);

	return 90 - (angle * 180 / M_PI);
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

float ShooterPitch::getSpeed()
{
	return pitch_angle->Get();
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
