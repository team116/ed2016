#include <Subsystems/Shooter.h>
#include <RobotMap.h>

Shooter* Shooter::INSTANCE = nullptr;

Shooter::Shooter() : Subsystem("Shooter")
{
	left_shooter_wheel = new CANTalon(Robot::LEFT_SHOOTER_MOTOR);
	right_shooter_wheel = new CANTalon(Robot::RIGHT_SHOOTER_MOTOR);

}


void Shooter::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::setShooterDirection(ShooterDirection value)
{
	if (value == ShooterDirection::SHOOT_OUT)
	{
		left_shooter_wheel->Set(1.0);
		right_shooter_wheel->Set(1.0);
	}
	else if (value == ShooterDirection::SHOOT_STILL)
	{
		left_shooter_wheel->Set(0.0);
		right_shooter_wheel->Set(0.0);
	}
	else if (value == ShooterDirection::SHOOT_IN)
	{
		left_shooter_wheel->Set(-1.0);
		right_shooter_wheel->Set(-1.0);
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
