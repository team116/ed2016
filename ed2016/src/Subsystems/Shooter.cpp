#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include <Subsystems/Sensors.h>
#include <CommandBase.h>
#include <Subsystems/Shooter.h>


const float Shooter::RPM_PRESETS[] = {
	666.67,
	1333.34,
	2000.01,
	2666.68,
	333.35,
	4000.0
};

const float Shooter::SPEED_PRESETS[] = {
	0.1666666666666,
	0.3333333333333,
	0.5,
	0.6666666666666,
	0.8333333333333,
	1.0
};
	Shooter::Shooter() :
		PIDSubsystem("ShooterPID", 1.0, 0.0, 0.0)
{
	top_shooter_wheel = new MOTOR_TYPE(RobotPorts::TOP_SHOOTER_MOTOR);
	bottom_shooter_wheel = new MOTOR_TYPE(RobotPorts::BOTTOM_SHOOTER_MOTOR);
	SetInputRange(0.0, 4000.0);
	SetOutputRange(0.0, 1.0);
	SetSetpoint(Shooter::RPM_PRESETS[CommandBase::oi->getShooterSpeedPosition()]);
	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
}

double Shooter::ReturnPIDInput()
{
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	float test =  (CommandBase::sensors->getTach());
	test = (test * 60);
	return test;

	// yourPot->SetAverageVoltage() / kYourMaxVoltage;
}
void Shooter::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);

	top_shooter_wheel->Set(output);
	bottom_shooter_wheel->Set(output);


}

void Shooter::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
}

float Shooter::getRPMPreset(int preset)
{
	return RPM_PRESETS[preset];
}

float Shooter::getSpeedPreset(int preset)
{
	return SPEED_PRESETS[preset];
}

void Shooter::setShooterSpeed(float speed){
	top_shooter_wheel->Set(speed);
	bottom_shooter_wheel->Set(speed);
}

