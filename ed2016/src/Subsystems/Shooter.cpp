#include <Commands/RunShooterWheels.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/ShooterPitch.h>
#include <RobotMap.h>
#include <Subsystems/Sensors.h>
#include <Log.h>
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"

const float Shooter::RPM_PRESETS[] = {
	1350.0,
	1620.0,
	1890.0,
	2160.0,
	2430.0,
	2700.0
};

const float Shooter::SPEED_PRESETS[] = {
	0.5,
	0.6,
	0.7,
	0.8,
	0.9,
	1.0
};

Shooter::Shooter() : PIDSubsystem("Shooter", 0.0000003, 0.00000000000001, 0.0)
{
	shooter_wheel = Utils::constructMotor(RobotPorts::SHOOTER_MOTOR);

	SetInputRange(0, 5000);
	SetAbsoluteTolerance(10);
	SetOutputRange(-1.0,1.0);

	speed = 0;
}

void Shooter::InitDefaultCommand()
{
	SetDefaultCommand(new RunShooterWheels());
}

double Shooter::ReturnPIDInput()
{
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;
	CommandBase::log->write(Log::DEBUG_LEVEL, "PID Input: %f Target: %f P: %F I: %F D: %F", CommandBase::sensors->speedShooterWheel(), GetSetpoint(), GetPIDController()->GetP(), GetPIDController()->GetI(), GetPIDController()->GetD());
	//DriverStation::ReportError("Input: " + std::to_string(CommandBase::sensors->speedShooterWheel()) + " Target: " + std::to_string(GetSetpoint()) + " P: " + std::to_string(getP()) + " I: " + std::to_string(getI()) + " D: " + std::to_string(getD()));
	return CommandBase::sensors->speedShooterWheel();
}

void Shooter::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	if(GetPIDController()->IsEnabled()) {
		speed = Utils::boundaryCheck((speed + output), -1.0, 1.0);
		CommandBase::log->write(Log::DEBUG_LEVEL, "PID Output: %f Set: %f", output, speed);
		//DriverStation::ReportError("Output: " + std::to_string(output) + " Speed: " + std::to_string(speed));
		shooter_wheel->Set(speed);
	}
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::setShooterSpeed(float speed)
{
	shooter_wheel->Set(speed);
}

float Shooter::getRPMPreset(int preset)
{
	return RPM_PRESETS[preset];
}

float Shooter::getSpeedPreset(int preset)
{
	return SPEED_PRESETS[preset];
}

//Returns necessary shooter rpm speed
//Angle of ball launch, NOT angle of shooter. Should be angle perpendicular to shooter
float Shooter::getSpeedToTarget(float angle)
{
	//sqrt(-2gy)/sin(theta) * 60 / (2*pi*r)
	return (sqrt(1960 * CommandBase::shooter_pitch->SHOOTER_TO_TARGET_HEIGHT) / sin(angle) * 60) / (10.16 * M_PI);
}

float Shooter::getMotorSpeed()
{
	return shooter_wheel->Get();
}

float Shooter::getP()
{
	return GetPIDController()->GetP();
}
float Shooter::getI()
{
	return GetPIDController()->GetI();
}
float Shooter::getD()
{
	return GetPIDController()->GetD();
}
float Shooter::getF()
{
	return GetPIDController()->GetF();
}

void Shooter::setP(float p)
{
	GetPIDController()->SetPID(p, getI(), getD());
}
void Shooter::setI(float i)
{
	GetPIDController()->SetPID(getP(), i, getD());
}
void Shooter::setD(float d)
{
	GetPIDController()->SetPID(getP(), getI(), d);
}
void Shooter::setF(float f)
{
	GetPIDController()->SetPID(getP(), getI(), getD(), f);
}
