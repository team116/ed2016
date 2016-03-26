#include "Winches.h"
#include "../RobotMap.h"
#include <CommandBase.h>
#include <Subsystems/Sensors.h>

const float Winches::WINCH_SPEED = 1.0; //temporary speed
const float Winches::WINCH_CURRENT_SPIKE_THRESHHOLD = 10.0;	//random guess, no idea what this number is actually supposed to look like
const float Winches::PID_BASE_SPEED = 0.5;

Winches::Winches() :
		PIDSubsystem("Winches", 0.01, 0.0, 0.0)
{
	SetInputRange(-180, 180);
	SetOutputRange(-1.0, 1.0);
	GetPIDController()->SetContinuous(false);
	SetAbsoluteTolerance(10.0);
	Disable();

	front_winch = Utils::constructMotor(RobotPorts::WINCH_MOTOR_FRONT);
	back_winch = Utils::constructMotor(RobotPorts::WINCH_MOTOR_BACK);

	back_winch_direction = Utils::VerticalDirection::V_STILL;
	front_winch_direction = Utils::VerticalDirection::V_STILL;
}

void Winches::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

double Winches::ReturnPIDInput()
{
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;

	DriverStation::ReportError("Robot Pitch: " + std::to_string(CommandBase::sensors->robotPitch()));
	return CommandBase::sensors->robotPitch();
}

void Winches::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);

	if(isPIDEnabled())
	{
		front_winch->Set(Utils::boundaryCheck((-PID_BASE_SPEED + output), -1.0, 1.0));
		DriverStation::ReportError("Front Winch: " + std::to_string(-PID_BASE_SPEED + output));
		back_winch->Set(-PID_BASE_SPEED);
	}
}


void Winches::setFrontWinchDirection(Utils::VerticalDirection direction)
{
	front_winch_direction = direction;
	if (direction == Utils::VerticalDirection::UP)
	{
		setFrontWinchSpeed(-WINCH_SPEED);
	}
	else if (direction == Utils::VerticalDirection::DOWN)
	{
		setFrontWinchSpeed(WINCH_SPEED);
	}
	else
	{
		setFrontWinchSpeed(0.0);
	}
}

void Winches::setBackWinchDirection (Utils::VerticalDirection direction)
{
	back_winch_direction = direction;
	if (direction == Utils::VerticalDirection::UP)
	{
		setBackWinchSpeed(-WINCH_SPEED);
	}
	else if (direction == Utils::VerticalDirection::DOWN)
	{
		setBackWinchSpeed(WINCH_SPEED);
	}
	else
	{
		setBackWinchSpeed(0.0);
	}
}

void Winches::setFrontWinchSpeed(float speed) {
	front_winch->Set(Utils::boundaryCheck(speed, -1.0, 1.0));
	if (speed < 0.0)
	{
		front_winch_direction = Utils::VerticalDirection::UP;
	}
	else if (speed > 0.0)
	{
		front_winch_direction = Utils::VerticalDirection::DOWN;
	}
	else
	{
		front_winch_direction = Utils::VerticalDirection::V_STILL;
	}
}

void Winches::setBackWinchSpeed(float speed) {
	back_winch->Set(Utils::boundaryCheck(-speed, -1.0, 1.0));
	if (speed < 0.0)
	{
		back_winch_direction = Utils::VerticalDirection::UP;
	}
	else if (speed > 0.0)
	{
		back_winch_direction = Utils::VerticalDirection::DOWN;
	}
	else
	{
		back_winch_direction = Utils::VerticalDirection::V_STILL;
	}
}

Utils::VerticalDirection Winches::getFrontWinchDirection()
{
	return front_winch_direction;
}

Utils::VerticalDirection Winches::getBackWinchDirection()
{
	return back_winch_direction;
}

bool Winches::isWinchCurrentSpiking()
{
	Log::getInstance()->write(Log::INFO_LEVEL, "Current Winch Current Front: %f Back: %f", CommandBase::sensors->getCurrent(RobotPorts::WINCH_MOTOR_FRONT),
			CommandBase::sensors->getCurrent(RobotPorts::WINCH_MOTOR_BACK));
	if (CommandBase::sensors->getCurrent(RobotPorts::WINCH_MOTOR_FRONT) > WINCH_CURRENT_SPIKE_THRESHHOLD
			&& CommandBase::sensors->getCurrent(RobotPorts::WINCH_MOTOR_BACK) > WINCH_CURRENT_SPIKE_THRESHHOLD)
	{
		return true;
	}
	else
		return false;
}

bool Winches::isPIDEnabled()
{
	return GetPIDController()->IsEnabled();
}

float Winches::getP()
{
	return GetPIDController()->GetP();
}
float Winches::getI()
{
	return GetPIDController()->GetI();
}
float Winches::getD()
{
	return GetPIDController()->GetD();
}
float Winches::getF()
{
	return GetPIDController()->GetF();
}

void Winches::setP(float p)
{
	GetPIDController()->SetPID(p, getI(), getD());
}
void Winches::setI(float i)
{
	GetPIDController()->SetPID(getP(), i, getD());
}
void Winches::setD(float d)
{
	GetPIDController()->SetPID(getP(), getI(), d);
}
void Winches::setF(float f)
{
	GetPIDController()->SetPID(getP(), getI(), getD(), f);
}
