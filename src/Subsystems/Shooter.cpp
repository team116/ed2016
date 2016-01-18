#include <Subsystems/Shooter.h>
#include <RobotMap.h>

Shooter* Shooter::INSTANCE = nullptr;

Shooter::Shooter() : Subsystem("Shooter")
{
	intake_roller = new CANTalon(1);
}

void Shooter::setIntakeDirection(IntakeDirection value)
{
	if (value == IntakeDirection::INTAKE_IN)
	{
		intake_roller->Set(-1.0);
	}
	else if (value == IntakeDirection::INTAKE_OUT)
	{
		intake_roller->Set(1.0);
	}
	else{
		intake_roller->Set(0.0);
	}
}

void Shooter::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

Shooter* Shooter::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Shooter();
	}
	return INSTANCE;
}
