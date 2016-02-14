#include <Subsystems/Shooter.h>
#include <RobotMap.h>

Shooter* Shooter::INSTANCE = nullptr;

Shooter::Shooter() : Subsystem("Shooter")
{
	top_shooter_wheel = new MOTOR_TYPE(RobotPorts::LEFT_SHOOTER_MOTOR);
	bottom_shooter_wheel = new MOTOR_TYPE(RobotPorts::RIGHT_SHOOTER_MOTOR);
	sensors = Sensors::getInstance();
}


void Shooter::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::turnShooterOn(bool on)
{
	if (on == true)
	{
		top_shooter_wheel->Set(1.0);
		bottom_shooter_wheel->Set(1.0);
	}
	else
	{
		top_shooter_wheel->Set(0.0);
		bottom_shooter_wheel->Set(0.0);
	}
}

Shooter* Shooter::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Shooter();
	}
	return INSTANCE;
}
