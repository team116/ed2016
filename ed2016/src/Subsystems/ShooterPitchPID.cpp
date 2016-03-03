#include "ShooterPitchPID.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"

#include <CommandBase.h>

const float ShooterPitchPID::MANUAL_SPEED = 1.0;
const float ShooterPitchPID::TARGET_HEIGHT = 246.38;//Centimeters to middle of target

ShooterPitchPID::ShooterPitchPID() :
		PIDSubsystem("ShooterPitchPID", 1.0, 0.0, 0.0)
{
	log = Log::getInstance();
	log->write(Log::DEBUG_LEVEL, "ShooterPitchPID Constructor begin");
	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.

	SmartDashboard::PutNumber("p-val", getP());
	log->write(Log::DEBUG_LEVEL, "After getP()");
	SmartDashboard::PutNumber("i-val", getI());
	log->write(Log::DEBUG_LEVEL, "After getI()");
	SmartDashboard::PutNumber("d-val", getD());
	log->write(Log::DEBUG_LEVEL, "After getD()");

	pitch_angle = Utils::constructMotor(RobotPorts::SHOOTER_PITCH_MOTOR);
	log->write(Log::DEBUG_LEVEL, "After constructMotor()");

	SetInputRange(0, 360);
	log->write(Log::DEBUG_LEVEL, "After SetInputRange");

	SetOutputRange(-1.0,1.0);
	log->write(Log::DEBUG_LEVEL, "After SetOutputRange");

	GetPIDController()->SetContinuous(false);
	log->write(Log::DEBUG_LEVEL, "ShooterPitchPID Constructor end");
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
float ShooterPitchPID::getPitchToTarget(PitchType type)
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

float ShooterPitchPID::getP()
{
	return GetPIDController()->GetP();
}
float ShooterPitchPID::getI()
{
	return GetPIDController()->GetI();
}
float ShooterPitchPID::getD()
{
	return GetPIDController()->GetD();
}

void ShooterPitchPID::setP(float p)
{
	GetPIDController()->SetPID(p, getI(), getD());
}
void ShooterPitchPID::setI(float i)
{
	GetPIDController()->SetPID(getP(), i, getD());
}
void ShooterPitchPID::setD(float d)
{
	GetPIDController()->SetPID(getP(), getI(), d);
}
