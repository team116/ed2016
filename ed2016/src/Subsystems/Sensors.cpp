#include <Commands/CheckLidar.h>
#include <Subsystems/Sensors.h>
#include <RobotMap.h>
#include <WPILib.h>
#include <NAVX/AHRS.h>

// get access to pi const: M_PI
#define _USE_MATH_DEFINES
#include <math.h>

const float Sensors::SHOOTER_ANGLE_OFFSET = 0.0;
const float Sensors::INTAKE_ANGLE_OFFSET = 0.0;
const float Sensors::DRIVE_WHEEL_DIAMETER = 3.13;
const int Sensors::DRIVE_WHEEL_PPR = 128;
const int Sensors::SHOOTER_WHEEL_PPR = 2;

Sensors::Sensors() : Subsystem("Sensors") // constructor for sensors
{
	last_count = 0;

	timer = new Timer();

	shooter_angle_encoder = new AnalogInput(RobotPorts::SHOOTER_ANGLE_ENCODER);
	intake_angle_encoder = new AnalogInput(RobotPorts::INTAKE_ANGLE_ENCODER);

	shooter_home_switch = new DigitalInput(RobotPorts::SHOOTER_HOME_SWITCH);

	intake_limit_switch = new DigitalInput(RobotPorts::INTAKE_LIMIT);

	top_shooter_wheel_tach = new Counter(RobotPorts::TOP_SHOOTER_WHEEL_TACH);
	bottom_shooter_wheel_tach = new Counter(RobotPorts::BOTTOM_SHOOTER_WHEEL_TACH);

	top_shooter_wheel_tach->ClearDownSource();
	bottom_shooter_wheel_tach->ClearDownSource();
	prev_top_tach_count = 0;
	prev_bottom_tach_count = 0;
	top_tach_rate = 0.0;
	bottom_tach_rate = 0.0;

	cycle_timer = new Timer();
	cycle_timer->Start();
	cycle_timer->Reset();
	prev_time_stamp = cycle_timer->Get();

	ready_to_shoot_balls_switch = new DigitalInput(RobotPorts::BALL_PREP_CHECK_LIMIT);

	left_drive_encoder = new Encoder(RobotPorts::LEFT_ENCODER_A, RobotPorts::LEFT_ENCODER_B);
	right_drive_encoder = new Encoder(RobotPorts::RIGHT_ENCODER_A, RobotPorts::RIGHT_ENCODER_B);
	left_drive_encoder->SetDistancePerPulse(2.0 * M_PI * DRIVE_WHEEL_DIAMETER / (float)DRIVE_WHEEL_PPR);
	right_drive_encoder->SetDistancePerPulse(2.0 * M_PI * DRIVE_WHEEL_DIAMETER / (float)DRIVE_WHEEL_PPR);
	//shooter_ready_to_shoot = new DigitalInput(RobotPorts::BALL_PREP_CHECK_LIMIT);


	lidar_distance = 0;
	lidar = new I2C(I2C::Port::kOnboard, RobotPorts::LIDAR_ADDRESS);

	navx = new AHRS(I2C::Port::kMXP);

	drive_encoders_enabled = true;
	lidar_sensor_enabled = true;
	shooter_angle_enabled = true;
	robot_angle_enabled = true;
	intake_angle_enabled = true;
	ready_to_shoot_enabled = false;
	shooter_wheel_tachometer_enabled = true;
}

void Sensors::InitDefaultCommand()
{
	SetDefaultCommand(new CheckLidar());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

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
		if (Utils::getRobotType() == Utils::CAN_MOTOR_BOT)
		{
			return navx->GetYaw();
		}
		else if (Utils::getRobotType() == Utils::ED2016_BOT)
		{
			return navx->GetRoll();
		}
		else
		{
			return 0.0;
		}
	}
	else
	{
		return 0.0;
	}
}

float Sensors::speedTopShooterWheel()
{
	{
		if (shooter_wheel_tachometer_enabled)
		{
			return top_tach_rate;
		}
		else
		{
			return 0.0;
		}
	}
}

float Sensors::speedBottomShooterWheel()
{
	{
		if (shooter_wheel_tachometer_enabled)
		{
			return bottom_tach_rate;
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
	return ready_to_shoot_balls_switch->Get();
}
bool Sensors::shooterWheelTachometerEnabled()
{
	return shooter_wheel_tachometer_enabled;
}
bool Sensors::isShooterHomeSwitchHorizontal()
{
	if(ready_to_shoot_enabled) {
		return shooter_home_switch->Get();
	}
	else {
		return false;
	}
}

float Sensors::getSpeedLeft()
{
	return 0.0;
}

float Sensors::getSpeedRight()
{
	return 0.0;
}

void Sensors::updateTachometers()
{
	unsigned int cur_top_count = top_shooter_wheel_tach->Get();
	unsigned int cur_bottom_count = bottom_shooter_wheel_tach->Get();
	float cycle_time = getCycleTime();

	// multiply by 60 to convert to RPM
	top_tach_rate = (float)(cur_top_count - prev_top_tach_count) / cycle_time * 60.0;
	bottom_tach_rate = (float)(cur_bottom_count - prev_bottom_tach_count) / cycle_time * 60.0;

	prev_top_tach_count = cur_top_count;
	prev_bottom_tach_count = cur_bottom_count;
}

float Sensors::getCycleTime()
{
	return cycle_timer->Get() - prev_time_stamp;
}

void Sensors::updateCycleTime()
{
	prev_time_stamp = cycle_timer->Get();
}
