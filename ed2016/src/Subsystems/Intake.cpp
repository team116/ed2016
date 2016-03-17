#include <RobotMap.h>
#include <Subsystems/Intake.h>

const int Intake::ANGLE_PRESET_COUNT = 6;
float* Intake::ANGLE_PRESETS = new float[Intake::ANGLE_PRESET_COUNT];/* {
	-15.0,
	6.0,
	27.0,
	48.0,
	69.0,
	90.0
};*/

Intake::Intake() : Subsystem("Intake")
{
	intake_roller = Utils::constructMotor(RobotPorts::INTAKE_ROLLER_MOTOR);
	intake_angle = Utils::constructMotor(RobotPorts::INTAKE_ANGLE_MOTOR);

	for (int i = 0; i < ANGLE_PRESET_COUNT; ++i)
	{
		ANGLE_PRESETS[i] = -15.0 + (float)i * 21.0; // [-15, 90]
	}

	log = Log::getInstance();
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
		intake_angle->Set(-1.0);
	}
	else if (value == Utils::VerticalDirection::DOWN)
	{
		intake_angle->Set(1.0);
	}
	else if (value == Utils::VerticalDirection::V_STILL)
	{
		intake_angle->Set(0.0);
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
