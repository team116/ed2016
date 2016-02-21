<<<<<<< Updated upstream
#include <Subsystems/Shooter.h>
#include <RobotMap.h>

Shooter* Shooter::INSTANCE = nullptr;

Shooter::Shooter() : Subsystem("Shooter")
{
	top_shooter_wheel = new MOTOR_TYPE(RobotPorts::LEFT_SHOOTER_MOTOR);
	bottom_shooter_wheel = new MOTOR_TYPE(RobotPorts::RIGHT_SHOOTER_MOTOR);
	pitch_angle = new MOTOR_TYPE(RobotPorts::SHOOTER_PITCH_MOTOR);
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

void Shooter::setShooterPitchDirection(ShooterPitchDirection dir)
{
	//Note: 1.0 and -1.0 may need to be reversed
	if(dir == SHOOTER_UP)
	{
		pitch_angle->Set(1.0);
	}
	else if (dir == SHOOTER_DOWN){
		pitch_angle->Set(-1.0);
	}
	else
	{
		pitch_angle->Set(0.0);
	}
}

PIDOutput* Shooter::getShooterPIDOutput()
{
	return pitch_angle;
}

Shooter* Shooter::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Shooter();
	}
	return INSTANCE;
}
=======
#include <Commands/RunShooterWheels.h>
#include <Subsystems/Shooter.h>
#include <RobotMap.h>

const float Shooter::RPM_PRESETS[] = {
	750.0,
	1500.0,
	2250.0,
	3000.0,
	3750.0,
	4500.0
};

const float Shooter::SPEED_PRESETS[] = {
	0.1666666666666,
	0.3333333333333,
	0.5,
	0.6666666666666,
	0.8333333333333,
	1.0
};

Shooter::Shooter() : Subsystem("Shooter")
{
	top_shooter_wheel = new MOTOR_TYPE(RobotPorts::TOP_SHOOTER_MOTOR);
	bottom_shooter_wheel = new MOTOR_TYPE(RobotPorts::BOTTOM_SHOOTER_MOTOR);
	pitch_angle = new MOTOR_TYPE(RobotPorts::SHOOTER_PITCH_MOTOR);
}


void Shooter::InitDefaultCommand()
{
	// no default command
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::setShooterSpeed(float speed)
{
	top_shooter_wheel->Set(speed);
	bottom_shooter_wheel->Set(-speed);
}

float Shooter::getRPMPreset(int preset)
{
	return RPM_PRESETS[preset];
}

float Shooter::getSpeedPreset(int preset)
{
	return SPEED_PRESETS[preset];
}
>>>>>>> Stashed changes
