#include <Subsystems/Sensors.h>
#include <RobotMap.h>
#include <WPILib.h>

Sensors* Sensors::INSTANCE = nullptr;

const float Sensors::SHOOTER_ANGLE_OFFSET = 0.0;
const float Sensors::INTAKE_ANGLE_OFFSET = 0.0;

Sensors::Sensors() : Subsystem("Sensors")
{
	shooter_angle_encoder = new AnalogInput(Robot::SHOOTER_ANGLE_ENCODER);


}

void Sensors::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
bool Sensors::isReadyToShoot()
{
	return false;
}

float Sensors::shooterAngle()
{
	return 360.0 * shooter_angle_encoder->GetVoltage() / 5.0 - SHOOTER_ANGLE_OFFSET;
}
float Sensors::robotAngle()
{
	return 0.0;
}
float Sensors::speedLeftShooterWheel()
{
	return 0.0;
}
float Sensors::speedRightShooterWheel()
{
	return 0.0;
}
float Sensors::intakeAngle()
{
	return 360.0 * intake_angle_encoder->GetVoltage() / 5.0 - INTAKE_ANGLE_OFFSET;
}
float Sensors::lidarDistance()
{
	return 0.0;
}
Sensors* Sensors::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Sensors();
	}
	return INSTANCE;

}
