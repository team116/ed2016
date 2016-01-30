#include <Commands/CheckLidar.h>
#include <Subsystems/Sensors.h>
#include <RobotMap.h>
#include <WPILib.h>
#include <NAVX/AHRS.h>

Sensors* Sensors::INSTANCE = nullptr;

const float Sensors::SHOOTER_ANGLE_OFFSET = 0.0;
const float Sensors::INTAKE_ANGLE_OFFSET = 0.0;

Sensors::Sensors() : Subsystem("Sensors") // constructor for sensors
{
	shooter_angle_encoder = new AnalogInput(Robot::SHOOTER_ANGLE_ENCODER);
	left_shooter_wheel_tach_input = new DigitalInput(Robot::LEFT_SHOOTER_WHEEL_TACH);
	right_shooter_wheel_tach_input = new DigitalInput(Robot::RIGHT_SHOOTER_WHEEL_TACH);
	intake_angle_encoder = new AnalogInput(Robot::INTAKE_ANGLE_ENCODER);
	left_shooter_wheel_tach = new Encoder(left_shooter_wheel_tach_input, nullptr);
	right_shooter_wheel_tach = new Encoder(right_shooter_wheel_tach_input, nullptr);
	right_shooter_wheel_tach->SetDistancePerPulse(0.0078125); // 1 divided by 128
	left_shooter_wheel_tach->SetDistancePerPulse(0.0078125); // 1 divided by 128
	lidar_distance = 0;
	lidar = new I2C(I2C::Port::kOnboard, Robot::LIDAR_ADDRESS);

}

void Sensors::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new CheckLidar());
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
	return left_shooter_wheel_tach->GetRate();
}

float Sensors::speedRightShooterWheel()
{
	return left_shooter_wheel_tach->GetRate();
}

float Sensors::intakeAngle()
{
	return 360.0 * intake_angle_encoder->GetVoltage() / 5.0 - INTAKE_ANGLE_OFFSET;
}

int Sensors::lidarDistance()
{
	return lidar_distance;
}

void Sensors::refreshLidar()
{
	if (lidar->Write(Robot::LIDAR_INIT_REGISTER, 4) != 0)
	{
		uint8_t buffer[2];
		while (lidar->Read(Robot::LIDAR_RANGE_REGISTER, 2, buffer) != 0) { } // the Read function does everything

		 lidar_distance = (buffer[0] << 8) + buffer[1];
	}
}

Sensors* Sensors::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Sensors();
	}
	return INSTANCE;

}

void Sensors::resetEncoderLeft() {
	 left_drive_encoder_a->Reset();
}

void Sensors::resetEncoderRight() {
	right_drive_encoder_a->Reset();
}
