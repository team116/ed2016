#include <Subsystems/Mobility.h>
#include <RobotMap.h>
#include <Commands/JoystickDrive.h>
#include <Subsystems/Cameras.h>

const float PID_MIN = 0.13;
const float PID_MAX = 0.5;

const int Mobility::CYCLES_FOR_ONTARGET = 5;
const int Mobility::ONTARGET_TOLERANCE = 5;

Mobility::Mobility() : PIDSubsystem("Mobility", 0.37, 0.0, 0.0)
{
	leftFront = Utils::constructMotor(RobotPorts::LEFT_FRONT_MOTOR);
	leftBack = Utils::constructMotor(RobotPorts::LEFT_BACK_MOTOR);
	rightFront = Utils::constructMotor(RobotPorts::RIGHT_FRONT_MOTOR);
	rightBack = Utils::constructMotor(RobotPorts::RIGHT_BACK_MOTOR);

	front_orientation = true; // just to get rid of uninitialized warning
	useFrontOrientation(false); // this is the actual initializer

	SetInputRange(-320, 320);
	SetOutputRange(-1.0, 1.0);
	GetPIDController()->SetContinuous(true);
	Disable();
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

void Mobility::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new JoystickDrive());
}

double Mobility::ReturnPIDInput()
{
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;

	DriverStation::ReportError("Angle: " + std::to_string(CommandBase::cameras->HorizontalPixelsFromTarget()) + " Target: " + std::to_string(GetSetpoint()));

	return CommandBase::cameras->HorizontalPixelsFromTarget();
}

void Mobility::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	if(isPIDEnabled()) {
		if(fabs(GetPIDController()->GetError()) > ONTARGET_TOLERANCE) {
			if(output < 0) {
				output = Utils::boundaryCheck(output, -PID_MAX, -PID_MIN);
			}
			else if(output > 0) {
				output = Utils::boundaryCheck(output, PID_MIN, PID_MAX);
			}
		}
		else {
			output = 0;
		}
		DriverStation::ReportError("Output: " + std::to_string(output));
		setLeft(-output);
		setRight(output);

		checkTarget();
	}
}

void Mobility::setStraight(float speed)
{
	setLeft(speed);
	setRight(speed);
}

void Mobility::setLeft(float speed)
{
	if (front_orientation)
	{
		leftFront->Set(-speed);
		leftBack->Set(-speed);
	}
	else
	{
		leftFront->Set(speed);
		leftBack->Set(speed);
	}
}

void Mobility::setRight(float speed)
{
	if (front_orientation)
	{
		rightFront->Set(speed);
		rightBack->Set(speed);
	}
	else
	{
		rightFront->Set(-speed);
		rightBack->Set(-speed);
	}
}

void Mobility::useFrontOrientation(bool front)
{
	front_orientation = front;
}

float Mobility::getLeft()
{
	return leftBack->Get();
}
float Mobility::getRight()
{
	return rightBack->Get();
}

bool Mobility::isPIDEnabled()
{
	return GetPIDController()->IsEnabled();
}

float Mobility::getP()
{
	return GetPIDController()->GetP();
}
float Mobility::getI()
{
	return GetPIDController()->GetI();
}
float Mobility::getD()
{
	return GetPIDController()->GetD();
}
float Mobility::getF()
{
	return GetPIDController()->GetF();
}

void Mobility::setP(float p)
{
	GetPIDController()->SetPID(p, getI(), getD());
}
void Mobility::setI(float i)
{
	GetPIDController()->SetPID(getP(), i, getD());
}
void Mobility::setD(float d)
{
	GetPIDController()->SetPID(getP(), getI(), d);
}
void Mobility::setF(float f)
{
	GetPIDController()->SetPID(getP(), getI(), getD(), f);
}

bool Mobility::OnTarget()
{
	if(cycles_within_tolerance >= CYCLES_FOR_ONTARGET)
	{
		return true;
	}
	return false;
}

void Mobility::checkTarget()
{
	if(fabs(GetPIDController()->GetError()) < ONTARGET_TOLERANCE)
	{
		//Has to be in its own if statement because otherwise it would reset the cycle count every time it reached the max
		if(cycles_within_tolerance < CYCLES_FOR_ONTARGET)
		{
			cycles_within_tolerance++;
		}
	}
	else
	{
		//CommandBase::log->write(Log::DEBUG_LEVEL, "Resetting cycles. Error: %f", GetPIDController()->GetError());
		cycles_within_tolerance = 0;
	}
}
