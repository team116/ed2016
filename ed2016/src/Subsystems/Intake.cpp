#include <RobotMap.h>
#include <Subsystems/Intake.h>

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

void Intake::setIntakeDirection(Utils::HorizontalDirection value)
{
	if (value == Utils::HorizontalDirection::IN)
	{
		intake_roller->Set(-1.0);
	}
	else if (value == Utils::HorizontalDirection::OUT)
	{
		intake_roller->Set(1.0);
	}
	else if (value == Utils::HorizontalDirection::H_STILL)
	{
		intake_roller->Set(0.0);
	}
}

void Intake::setIntakeAngleDirection(Utils::VerticalDirection value)
{
	/* Note: may need to switch 1 and -1 */
	if (value == Utils::VerticalDirection::UP)
		{
			intake_angle->Set(1.0);
		}
		else if (value == Utils::VerticalDirection::DOWN)
		{
			intake_angle->Set(-1.0);
		}
		else if (value == Utils::VerticalDirection::V_STILL)
		{
			intake_angle->Set(0.0);
		}
}
