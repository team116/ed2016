#include "ShooterPID.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include <CommandBase.h>
#include <Subsystems/Sensors.h>
#include <Log.h>

const float ShooterPID::RPM_PRESETS[] = {
	2250.0,
	2700.0,
	3150.0,
	3600.0,
	4050.0,
	4500.0
};

const float ShooterPID::SPEED_PRESETS[] = {
	0.5,
	0.6,
	0.7,
	0.8,
	0.9,
	1.0
};

ShooterPID::ShooterPID() :
		PIDSubsystem("ShooterPID", 1.0, 0.0, 0.0)
{
	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.

	shooter_wheel = Utils::constructMotor(RobotPorts::SHOOTER_MOTOR);

	SetInputRange(0, 5000);
	SetAbsoluteTolerance(10);
	SetOutputRange(-1.0,1.0);
}

double ShooterPID::ReturnPIDInput()
{
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;
	CommandBase::log->write(Log::DEBUG_LEVEL, "PID Input: %f", CommandBase::sensors->speedShooterWheel());
	return CommandBase::sensors->speedShooterWheel();
}

void ShooterPID::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	CommandBase::log->write(Log::DEBUG_LEVEL, "PID Output: %f", output);
	shooter_wheel->Set(output);
}

void ShooterPID::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
}

void ShooterPID::setShooterSpeed(float speed)
{
	shooter_wheel->Set(speed);
}

float ShooterPID::getRPMPreset(int preset)
{
	return RPM_PRESETS[preset];
}

float ShooterPID::getSpeedPreset(int preset)
{
	return SPEED_PRESETS[preset];
}

//Returns necessary shooter rpm speed
//Angle of ball launch, NOT angle of shooter. Should be angle perpendicular to shooter
float ShooterPID::getSpeedToTarget(float angle)
{
	//sqrt(-2gy)/sin(theta) * 60 / (2*pi*r)
	return (sqrt(1960 * CommandBase::shooter_pitch->TARGET_HEIGHT) / sin(angle) * 60) / (10.16 * M_PI);
}

float ShooterPID::getP()
{
	return GetPIDController()->GetP();
}
float ShooterPID::getI()
{
	return GetPIDController()->GetI();
}
float ShooterPID::getD()
{
	return GetPIDController()->GetD();
}
float ShooterPID::getF()
{
	return GetPIDController()->GetF();
}

void ShooterPID::setP(float p)
{
	GetPIDController()->SetPID(p, getI(), getD());
}
void ShooterPID::setI(float i)
{
	GetPIDController()->SetPID(getP(), i, getD());
}
void ShooterPID::setD(float d)
{
	GetPIDController()->SetPID(getP(), getI(), d);
}
void ShooterPID::setF(float f)
{
	GetPIDController()->SetPID(getP(), getI(), getD(), f);
}
