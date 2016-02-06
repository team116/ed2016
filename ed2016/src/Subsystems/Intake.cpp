#include <RobotMap.h>
#include <Subsystems/Intake.h>

Intake* Intake::INSTANCE = nullptr;

Intake::Intake() : Subsystem("Intake")
{
	intake_roller = new MOTOR_TYPE(RobotPorts::INTAKE_ROLLER_MOTOR);
	intake_angle = new MOTOR_TYPE(RobotPorts::INTAKE_ANGLE_MOTOR);
}

void Intake::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void Intake::setIntakeDirection(Intake::IntakeDirection value)
{
	if (value == IntakeDirection::INTAKE_IN)
	{
		intake_roller->Set(-1.0);
	}
	else if (value == IntakeDirection::INTAKE_OUT)
	{
		intake_roller->Set(1.0);
	}
	else if (value == IntakeDirection::INTAKE_STILL)
	{
		intake_roller->Set(0.0);
	}
}

void Intake::setIntakeAngleDirection(IntakeAngleDirection value)
{
	/* Note: may need to switch 1 and -1 */
	if (value == IntakeAngleDirection::INTAKE_UP)
		{
			intake_angle->Set(1.0);
		}
		else if (value == IntakeAngleDirection::INTAKE_DOWN)
		{
			intake_angle->Set(-1.0);
		}
		else if (value == IntakeAngleDirection::INTAKE_STOP)
		{
			intake_angle->Set(0.0);
		}
}

Intake* Intake::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Intake();
	}
	return INSTANCE;
}
