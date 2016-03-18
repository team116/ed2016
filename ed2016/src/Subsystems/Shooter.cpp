#include <Commands/RunShooterWheels.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/ShooterPitch.h>
#include <RobotMap.h>

const float Shooter::RPM_PRESETS[] = {
	2250.0,
	2700.0,
	3150.0,
	3600.0,
	4050.0,
	4500.0
};

const float Shooter::SPEED_PRESETS[] = {
	0.5,
	0.6,
	0.7,
	0.8,
	0.9,
	1.0
};

Shooter::Shooter() : Subsystem("Shooter")
{
	shooter_wheel = Utils::constructMotor(RobotPorts::SHOOTER_MOTOR);
}


void Shooter::	InitDefaultCommand()
{
	SetDefaultCommand(new RunShooterWheels());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::setShooterSpeed(float speed)
{
	shooter_wheel->Set(speed);
}

float Shooter::getRPMPreset(int preset)
{
	return RPM_PRESETS[preset];
}

float Shooter::getSpeedPreset(int preset)
{
	return SPEED_PRESETS[preset];
}

//Returns necessary shooter rpm speed
//Angle of ball launch, NOT angle of shooter. Should be angle perpendicular to shooter
float Shooter::getSpeedToTarget(float angle)
{
	//sqrt(-2gy)/sin(theta) * 60 / (2*pi*r)
	return (sqrt(1960 * CommandBase::shooter_pitch->TARGET_HEIGHT) / sin(angle) * 60) / (10.16 * M_PI);
}
