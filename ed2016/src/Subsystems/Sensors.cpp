#include <Commands/CheckLidar.h>
#include <Subsystems/Sensors.h>
#include <RobotMap.h>
#include <WPILib.h>
#include <NAVX/AHRS.h>

// get access to pi const: M_PI
#define _USE_MATH_DEFINES
#include <math.h>

Sensors* Sensors::INSTANCE = nullptr;

const float Sensors::SHOOTER_ANGLE_OFFSET = 0.0;
const float Sensors::INTAKE_ANGLE_OFFSET = 0.0;
const float Sensors::DRIVE_WHEEL_DIAMETER = 3.13;
const int Sensors::DRIVE_WHEEL_PPR = 128;
const int Sensors::SHOOTER_WHEEL_PPR = 64;

Sensors::Sensors() : Subsystem("Sensors") // constructor for sensors
{
	shooter_angle_encoder = new AnalogInput(RobotPorts::SHOOTER_ANGLE_ENCODER);
	intake_angle_encoder = new AnalogInput(RobotPorts::INTAKE_ANGLE_ENCODER);

	left_shooter_wheel_tach_input = new DigitalInput(RobotPorts::LEFT_SHOOTER_WHEEL_TACH);
	right_shooter_wheel_tach_input = new DigitalInput(RobotPorts::RIGHT_SHOOTER_WHEEL_TACH);
	left_shooter_wheel_tach = new Encoder(left_shooter_wheel_tach_input, nullptr);
	right_shooter_wheel_tach = new Encoder(right_shooter_wheel_tach_input, nullptr);
	right_shooter_wheel_tach->SetDistancePerPulse(1.0 / (float)SHOOTER_WHEEL_PPR);
	left_shooter_wheel_tach->SetDistancePerPulse(1.0 / (float)SHOOTER_WHEEL_PPR);

	left_drive_encoder = new Encoder(RobotPorts::LEFT_ENCODER_A, RobotPorts::LEFT_ENCODER_B);
	right_drive_encoder = new Encoder(RobotPorts::RIGHT_ENCODER_A, RobotPorts::RIGHT_ENCODER_B);
	left_drive_encoder->SetDistancePerPulse(2.0 * M_PI * DRIVE_WHEEL_DIAMETER / (float)DRIVE_WHEEL_PPR);
	right_drive_encoder->SetDistancePerPulse(2.0 * M_PI * DRIVE_WHEEL_DIAMETER / (float)DRIVE_WHEEL_PPR);

	lidar_distance = 0;
	lidar = new I2C(I2C::Port::kOnboard, RobotPorts::LIDAR_ADDRESS);

	navx = new AHRS(I2C::Port::kMXP);

	drive_encoders_enabled = true;
	lidar_sensor_enabled = true;
	shooter_angle_enabled = true;
	robot_angle_enabled = true;
	intake_angle_enabled = true;
	ready_to_shoot_enabled = true;
	shooter_wheel_tachometer_enabled = true;
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
	if (ready_to_shoot_enabled);
{
	return false;
}
}

float Sensors::shooterAngle()
{
	if (shooter_angle_enabled)
{
		return 360.0 * shooter_angle_encoder->GetVoltage() / 5.0 - SHOOTER_ANGLE_OFFSET;
}
	else
	{
		return 0.0;
	}
}

float Sensors::robotAngle()
{
	if(robot_angle_enabled)
{
	#if ROBOT_TYPE == ANDERSON_BOT
		return navx->GetYaw();
	#elif ROBOT_TYPE == ED2016_BOT
		return navx->GetRoll();
	#else
		return 0.0;
	#endif
}
	else
	{
		return 0.0;
	}
}

float Sensors::speedLeftShooterWheel()
{
	{
		if (shooter_wheel_tachometer_enabled)
		{
	return left_shooter_wheel_tach->GetRate();
		}
		else
		{
			return 0.0;
		}
	}
}

float Sensors::speedRightShooterWheel()
{
	{
		if (shooter_wheel_tachometer_enabled)
		{
	return left_shooter_wheel_tach->GetRate();
		}
		else
		{
			return 0.0;
		}
	}
}

float Sensors::intakeAngle()
{
	if (intake_angle_enabled)
{
	return 360.0 * intake_angle_encoder->GetVoltage() / 5.0 - INTAKE_ANGLE_OFFSET;
}
	else
	{
		return 0.0;
	}
}

int Sensors::lidarDistance()
{
	if (lidar_sensor_enabled)
	{
		return lidar_distance;
	}
	else
	{
		return 0.0;
	}
}
void Sensors::refreshLidar()
{
	if (lidar->Write(RobotPorts::LIDAR_INIT_REGISTER, 4) != 0)
	{
		uint8_t buffer[2];
		while (lidar->Read(RobotPorts::LIDAR_RANGE_REGISTER, 2, buffer) != 0) { } // the Read function does everything

			 lidar_distance = (buffer[0] << 8) + buffer[1];
		}
	}

float Sensors::getDistanceLeft()
{
	if (drive_encoders_enabled)
	{
		return (float)left_drive_encoder->GetDistance();
	}
	else
	{
		return 0.0;
	}
}

float Sensors::getDistanceRight()
{
	if(drive_encoders_enabled)

	{
		return (float)right_drive_encoder->GetDistance();
	}
	else
	{
		return 0.0;
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

void Sensors::resetEncoderLeft()
{
	 left_drive_encoder->Reset();
}

void Sensors::resetEncoderRight()
{
	right_drive_encoder->Reset();
}

bool Sensors::areDriveEncoderEnabled()
{
	return drive_encoders_enabled;
}

bool Sensors::areLidarEnabled()
{
	return lidar_sensor_enabled;
}
bool Sensors::areShooterAngleEnabled()
{
	return shooter_angle_enabled;
}
bool Sensors::areRobotAngleEnabled()
{
	return robot_angle_enabled;
}
bool Sensors::areIntakeAngleEnabled()
{
	return intake_angle_enabled;
}
bool Sensors::readyToShoot()
{
	return ready_to_shoot_enabled;
}
bool Sensors::shooterWheelTachometerEnabled()
{
	return shooter_wheel_tachometer_enabled;
}


