#include <RobotMap.h>
#include <Subsystems/Intake.h>
#include <Subsystems/Sensors.h>
#include <CommandBase.h>

const int Intake::ANGLE_PRESET_COUNT = 6;
float* Intake::ANGLE_PRESETS = new float[Intake::ANGLE_PRESET_COUNT];/* {
	-15.0,
	6.0,
	27.0,
	48.0,
	69.0,
	90.0
};*/

Intake::Intake() : PIDSubsystem("Intake", 0.02, 0.0001, 0)
{
	intake_roller = Utils::constructMotor(RobotPorts::INTAKE_ROLLER_MOTOR);
	intake_angle = Utils::constructMotor(RobotPorts::INTAKE_ANGLE_MOTOR);

	for (int i = 0; i < ANGLE_PRESET_COUNT; ++i)
	{
		ANGLE_PRESETS[i] = -15.0 + (float)i * 21.0; // [-15, 90]
	}

	log = Log::getInstance();

	SetInputRange(-90, 120);
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
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;

	//CommandBase::log->write(Log::DEBUG_LEVEL, "");
	//CommandBase::log->write(Log::DEBUG_LEVEL, "Intake Angle: %f Target: %f P: %f I: %f D: %f", CommandBase::sensors->intakeAngle(), GetSetpoint(), getP(), getI(), getD());
	//DriverStation::ReportError("Angle: " + std::to_string(CommandBase::sensors->intakeAngle()) + " Target: " + std::to_string(GetSetpoint()));
	return CommandBase::sensors->intakeAngle();
}

void Intake::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	if(GetPIDController()->IsEnabled()) {
		//CommandBase::log->write(Log::DEBUG_LEVEL, "Intake Output: %f", output);
		//DriverStation::ReportError("Output: " + std::to_string(output));
		setSpeed(output);
	}
}

void Intake::setIntakeDirection(Utils::HorizontalDirection value)
{
	if (value == Utils::HorizontalDirection::IN)
	{
		setSpeed(1.0);
	}
	else if (value == Utils::HorizontalDirection::OUT)
	{
		setSpeed(-1.0);
	}
	else if (value == Utils::HorizontalDirection::H_STILL)
	{
		setSpeed(0.0);
	}
}

void Intake::setSpeed(float speed)
{
	intake_roller->Set(speed * -1);
}

void Intake::setIntakeAngleDirection(Utils::VerticalDirection value)
{
	/* Note: may need to switch 1 and -1 */
	if (value == Utils::VerticalDirection::UP)
	{
		setSpeed(-1.0);
	}
	else if (value == Utils::VerticalDirection::DOWN)
	{
		setSpeed(1.0);
	}
	else if (value == Utils::VerticalDirection::V_STILL)
	{
		setSpeed(0.0);
	}
	log->write(Log::ERROR_LEVEL, "intake angle speed: %f", intake_angle->Get());
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
