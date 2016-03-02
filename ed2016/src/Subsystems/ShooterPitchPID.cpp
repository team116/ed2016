#include "ShooterPitchPID.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"

#include <CommandBase.h>

const float ShooterPitchPID::MANUAL_SPEED = 1.0;
const float ShooterPitch::TARGET_HEIGHT = 246.38;//Centimeters to middle of target

ShooterPitchPID::ShooterPitchPID() :
		PIDSubsystem("ShooterPitchPID", 1.0, 0.0, 0.0)
{
	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.

	pitch_angle = Utils::constructMotor(RobotPorts::SHOOTER_PITCH_MOTOR);

	SetInputRange(0, 360);
	SetOutputRange(-1.0,1.0);
}

double ShooterPitchPID::ReturnPIDInput()
{
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;

	CommandBase::log->write(Log::DEBUG_LEVEL, "PID Input: %f", CommandBase::sensors->shooterAngle());
	return CommandBase::sensors->shooterAngle();
}

void ShooterPitchPID::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	CommandBase::log->write(Log::DEBUG_LEVEL, "PID Output: %f", output);
	pitch_angle->Set(output);
}

void ShooterPitchPID::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
}

void ShooterPitchPID::checkLimits()
{
	if(CommandBase::sensors->isShooterHomeSwitchHorizontal()) {
		CommandBase::sensors->zeroShooterPitch();
	}
}

///You should call Disable() to manually control the pitch, otherwise the PID will fight against you
void ShooterPitchPID::setDirection(Utils::VerticalDirection direction)
{
	switch(direction) {
	case Utils::VerticalDirection::UP:
		pitch_angle->Set(MANUAL_SPEED);
		break;
	case Utils::VerticalDirection::DOWN:
		pitch_angle->Set(-MANUAL_SPEED);
		break;
	case Utils::VerticalDirection::V_STILL:
		pitch_angle->Set(0.0);
		break;
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
