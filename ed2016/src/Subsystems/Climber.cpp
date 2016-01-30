#include <Subsystems/Climber.h>
#include <RobotMap.h>

Climber* Climber::INSTANCE = nullptr;

Climber::Climber():Subsystem("Climber")
{
	climber_armed_motor = new CANTalon(Robot::CLIMBER_ARMED_MOTOR);
	climber_direction = (ClimberMechanismDirection::CLIMBER_STILL);
}

void Climber::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
Climber::ClimberMechanismDirection Climber::getDirectionClimber()
{
	return climber_direction;
}
void Climber::setClimber(ClimberMechanismDirection direction) //function from .h to .cpp
{
	climber_direction = direction;
	if (direction == ClimberMechanismDirection::CLIMBER_UP)
	{
		climber_armed_motor->Set(0.5);
	}
	else if (direction == ClimberMechanismDirection::CLIMBER_DOWN)
	{
		climber_armed_motor->Set(-0.5);
	}
	else
	{
		climber_armed_motor->Set(0.0);
	}
}
Climber* Climber::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Climber();
	}
	return INSTANCE;
}
