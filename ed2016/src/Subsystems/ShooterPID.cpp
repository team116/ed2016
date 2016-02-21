#include "ShooterPID.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include <Subsystems/Sensors.h>
#include <CommandBase.h>

const float ShooterPID::RPM_PRESETS[] = {
	666.67,
	1333.34,
	2000.01,
	2666.68,
	333.35,
	4000.0
};

const float ShooterPID::SPEED_PRESETS[] = {
	0.1666666666666,
	0.3333333333333,
	0.5,
	0.6666666666666,
	0.8333333333333,
	1.0
};
	ShooterPID::ShooterPID() :
		PIDSubsystem("ShooterPID", 1.0, 0.0, 0.0)
{
	top_shooter_wheel = new MOTOR_TYPE(RobotPorts::TOP_SHOOTER_MOTOR);
	bottom_shooter_wheel = new MOTOR_TYPE(RobotPorts::BOTTOM_SHOOTER_MOTOR);

	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
}

double ShooterPID::ReturnPIDInput()
{
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	return ((CommandBase::sensors->getTopTachRate() + CommandBase::sensors->getBottomTachRate()) /2);

	// yourPot->SetAverageVoltage() / kYourMaxVoltage;
	return 0;
}
void ShooterPID::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);

	top_shooter_wheel->Set(output);
	bottom_shooter_wheel->Set(output);


}

void ShooterPID::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
}

float ShooterPID::getRPMPreset(int preset)
{
	return RPM_PRESETS[preset];
}

float ShooterPID::getSpeedPreset(int preset)
{
	return SPEED_PRESETS[preset];
}

void ShooterPID::setShooterSpeed(float speed){
	top_shooter_wheel->Set(speed);
	bottom_shooter_wheel->Set(speed);
}
