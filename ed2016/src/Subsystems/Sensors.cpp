#include <Subsystems/Sensors.h>
#include <RobotMap.h>
#include <WPILib.h>
#include <NAVX/AHRS.h>

Sensors* Sensors::INSTANCE = nullptr;

const float Sensors::SHOOTER_ANGLE_OFFSET = 0.0;

Sensors::Sensors() : Subsystem("Sensors")
{
	shooter_angle_encoder = new AnalogInput(Robot::SHOOTER_ANGLE_ENCODER);
	AHRS* test = new AHRS(I2C::Port::kMXP);
	test->GetAngle();
}

void Sensors::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
bool Sensors::isLimitSwitched()
{
	return false;
}

float Sensors::shooterAngle()
{
	return 360.0 * shooter_angle_encoder->GetVoltage() / 5.0 - SHOOTER_ANGLE_OFFSET;
}
Sensors* Sensors::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Sensors();
	}
	return INSTANCE;
}
