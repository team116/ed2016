#include <RobotMap.h>
#include <Subsystems/Intake.h>
#include <Subsystems/Sensors.h>
#include <CommandBase.h>

const int Intake::ANGLE_PRESET_COUNT = 6;
float* Intake::ANGLE_PRESETS = new float[Intake::ANGLE_PRESET_COUNT] {
	-30.0,
	-15.0,
	3.0,
	30.0,
	60.0,
	90.0
};

Intake::Intake() : PIDSubsystem("Intake", 0.02, 0.0001, 0)
{
	intake_angle = Utils::constructMotor(RobotPorts::INTAKE_ANGLE_MOTOR);

	/*
	for (int i = 0; i < ANGLE_PRESET_COUNT; ++i)
	{
		ANGLE_PRESETS[i] = -25.0 + (float)i * 21.0; // [-15, 90]
	}
	*/

	log = Log::getInstance();

	SetInputRange(-180.0, 180.0);
	SetAbsoluteTolerance(0.0);
	SetOutputRange(-1.0,1.0);

	GetPIDController()->SetContinuous(false);
}

void Intake::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

double Intake::ReturnPIDInput()
{
	//CommandBase::log->write(Log::DEBUG_LEVEL, "");
	//CommandBase::log->write(Log::DEBUG_LEVEL, "Intake Angle: %f Target: %f P: %f I: %f D: %f", CommandBase::sensors->intakeAngle(), GetSetpoint(), getP(), getI(), getD());
	//DriverStation::ReportError("Angle: " + std::to_string(CommandBase::sensors->intakeAngle()) + " Target: " + std::to_string(GetSetpoint()));
//	if (!CommandBase::sensors->isIntakeAngleEnabled())
//	{
//		Disable();
//	}
	return CommandBase::sensors->intakeAngle();
}

void Intake::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	if(GetPIDController()->IsEnabled()) {
		//CommandBase::log->write(Log::DEBUG_LEVEL, "Intake Output: %f", output);
		//DriverStation::ReportError("Output: " + std::to_string(output));
		setAngleSpeed(output);
	}
}

void Intake::setAngleSpeed(float speed)
{
	intake_angle->Set(-speed);
}

void Intake::setIntakeAngleDirection(Utils::VerticalDirection value)
{
	if (value == Utils::VerticalDirection::UP)
	{
		setAngleSpeed(0.5);
	}
	else if (value == Utils::VerticalDirection::DOWN)
	{
		setAngleSpeed(-0.5);
	}
	else if (value == Utils::VerticalDirection::V_STILL)
	{
		setAngleSpeed(0.0);
	}
}

float Intake::getAnglePreset(int index)
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

bool Intake::isPIDEnabled()
{
	return GetPIDController()->IsEnabled();
}

float Intake::getP()
{
	return GetPIDController()->GetP();
}
float Intake::getI()
{
	return GetPIDController()->GetI();
}
float Intake::getD()
{
	return GetPIDController()->GetD();
}
float Intake::getF()
{
	return GetPIDController()->GetF();
}

void Intake::setP(float p)
{
	GetPIDController()->SetPID(p, getI(), getD());
}
void Intake::setI(float i)
{
	GetPIDController()->SetPID(getP(), i, getD());
}
void Intake::setD(float d)
{
	GetPIDController()->SetPID(getP(), getI(), d);
}
void Intake::setF(float f)
{
	GetPIDController()->SetPID(getP(), getI(), getD(), f);
}
