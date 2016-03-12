#include <Commands/UpdateSensors.h>
#include <Subsystems/Sensors.h>
#include <RobotMap.h>
#include <WPILib.h>
#include <NAVX/AHRS.h>

// get access to pi const: M_PI
#define _USE_MATH_DEFINES
#include <math.h>

const float Sensors::MIN_SHOOTER_ANGLE_VOLT = 1.11;
const float Sensors::MAX_SHOOTER_ANGLE_VOLT = 2.31;
const float Sensors::INTAKE_ANGLE_OFFSET = 0.0;
const float Sensors::DRIVE_WHEEL_DIAMETER = 7.9502;
const int Sensors::DRIVE_WHEEL_PPR = 128;

const int Sensors::SHOOTER_WHEEL_PPR = 2;

Sensors::Sensors() : Subsystem("Sensors") // constructor for sensors
{
	log = Log::getInstance();

	shooter_angle_offset = 0.0;
	shooter_angle_encoder = new AnalogInput(RobotPorts::SHOOTER_ANGLE_ENCODER);

	shooter_angle_offset = 0.0;
	intake_angle_encoder = new AnalogInput(RobotPorts::INTAKE_ANGLE_ENCODER);
	shooter_home_switch = new DigitalInput(RobotPorts::SHOOTER_HOME_SWITCH);

	shooter_wheel_tach = new Counter(RobotPorts::SHOOTER_WHEEL_TACH);
	//top_shooter_wheel_tach = new Counter(RobotPorts::TOP_SHOOTER_WHEEL_TACH);
	//bottom_shooter_wheel_tach = new Counter(RobotPorts::BOTTOM_SHOOTER_WHEEL_TACH);

	shooter_wheel_tach->ClearDownSource();
	shooter_wheel_tach_rate = 0.0;
	cur_tach_period_index = 0;
	for (int i = 0; i < TACH_PERIOD_COUNT; ++i)
	{
		prev_tach_timestamps[i] = 0.0;
		prev_tach_counts[i] = 0;
	}

	cycle_timer = new Timer();
	cycle_timer->Start();
	cycle_timer->Reset();
	prev_time_stamp = cycle_timer->Get();

	ready_to_shoot_balls_switch = new DigitalInput(RobotPorts::BALL_PREP_CHECK_LIMIT);

	left_drive_encoder = new Encoder(RobotPorts::LEFT_ENCODER_A, RobotPorts::LEFT_ENCODER_B);
	right_drive_encoder = new Encoder(RobotPorts::RIGHT_ENCODER_A, RobotPorts::RIGHT_ENCODER_B);
	left_drive_encoder->SetDistancePerPulse(2.0 * M_PI * DRIVE_WHEEL_DIAMETER / (float)DRIVE_WHEEL_PPR);
	right_drive_encoder->SetDistancePerPulse(2.0 * M_PI * DRIVE_WHEEL_DIAMETER / (float)DRIVE_WHEEL_PPR);

	lidar_stage = 0;
	lidar_timer = new Timer();
	lidar_timer->Start();
	lidar_timer->Reset();
	lidar_distance = 0;
	lidar = new I2C(I2C::Port::kOnboard, RobotPorts::LIDAR_ADDRESS);

	navx = new AHRS(SPI::Port::kMXP);

	pdp = new PowerDistributionPanel(RobotPorts::PDP);

	drive_encoders_enabled = true;
	lidar_sensor_enabled = true;
	shooter_angle_enabled = true;
	robot_angle_enabled = true;
	intake_angle_enabled = true;
	ready_to_shoot_enabled = true;
	shooter_home_switch_enabled = false;
	shooter_wheel_tachometer_enabled = true;
}

void Sensors::InitDefaultCommand()
{
	SetDefaultCommand(new UpdateSensors());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Sensors::zeroShooterPitch()
{
	shooter_angle_offset = shooterAngleActual();
}

float Sensors::shooterAngleActual()
{
	return 90.0 * (shooter_angle_encoder->GetVoltage() - MIN_SHOOTER_ANGLE_VOLT) / (MAX_SHOOTER_ANGLE_VOLT - MIN_SHOOTER_ANGLE_VOLT);
}

float Sensors::shooterAngle()
{
	if (areShooterAngleEnabled())
	{
		float actual = shooterAngleActual();
		if (actual > 270.0)
		{
			return -(360.0 - actual);
		}
		else
		{
			return actual;
		}
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
			//log->write(Log::TRACE_LEVEL, "Robot angle: %f, %f, %f", navx->GetYaw(), navx->GetRoll(), navx->GetPitch());
			return navx->GetYaw();
		}
		else if (Utils::getRobotType() == Utils::ED2016_BOT)
		{
			return navx->GetYaw();
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

float Sensors::speedShooterWheel()
{
	{
		if (shooterWheelTachometerEnabled())
		{
			return shooter_wheel_tach_rate;
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
	if (areLidarEnabled())
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
	uint8_t lidar_range_copy;
	if (lidar_timer->Get() > (0.04 * (float)lidar_stage))
	{
		switch (lidar_stage)
		{
		case 0:
			lidar->Write(RobotPorts::LIDAR_INIT_REGISTER, 4);
			++lidar_stage;
			break;
		case 1:
			lidar_range_copy = RobotPorts::LIDAR_RANGE_REGISTER;
			lidar->WriteBulk(&lidar_range_copy, 1);
			++lidar_stage;
			break;
		case 2:
			uint8_t buffer[2];
			lidar->ReadOnly(2, buffer);
			lidar_distance = (buffer[0] << 8) + buffer[1];
			++lidar_stage;
			break;
		case 3:
			lidar_timer->Reset();
			lidar_stage = 0;
		}
	}
}

float Sensors::getDistanceLeft()
{
	if (areDriveEncoderEnabled())
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
	if(areDriveEncoderEnabled())

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
	if (ready_to_shoot_enabled)
	{
		return ready_to_shoot_balls_switch->Get();
	}
	else
	{
		return false;
	}
}

float Sensors::getCurrent(unsigned int port)
{
	return pdp->GetCurrent(port);
}

bool Sensors::isShooterHomeSwitchEnabled()
{
	return shooter_home_switch_enabled;
}

bool Sensors::shooterWheelTachometerEnabled()
{
	return shooter_wheel_tachometer_enabled;
}

bool Sensors::isShooterHomeSwitchHorizontal()
{
	if (isShooterHomeSwitchEnabled()) {
		return !shooter_home_switch->Get();
	}
	else {
		return false;
	}
}
float Sensors::getSpeedLeft()
{
	if (areDriveEncoderEnabled())
	{
		return left_drive_encoder->GetRate();
	}
	return 0.0;
}

float Sensors::getSpeedRight()
{
	if (areDriveEncoderEnabled())
	{
		return right_drive_encoder->GetRate();
	}
	return 0.0;
}

void Sensors::updateTachometers()
{
	unsigned int cur_tach_count = shooter_wheel_tach->Get();
	float cur_timestamp = cycle_timer->Get();

	shooter_wheel_tach_rate = (float)(cur_tach_count - prev_tach_counts[cur_tach_period_index]) / (cur_timestamp - prev_tach_timestamps[cur_tach_period_index]) * 60.0;
	char text[255];
	snprintf(text, 255, "tach rate: %f, prev count: %d, cur count: %d, prev time: %f, cur time: %f",
			shooter_wheel_tach_rate,
			prev_tach_counts[cur_tach_period_index],
			cur_tach_count,
			prev_tach_timestamps[cur_tach_period_index],
			cur_timestamp);
	DriverStation::ReportError(text);
	prev_tach_counts[cur_tach_period_index] = cur_tach_count;
	prev_tach_timestamps[cur_tach_period_index] = cur_timestamp;

	++cur_tach_period_index;
	if (cur_tach_period_index == TACH_PERIOD_COUNT)
	{
		cur_tach_period_index = 0;
	}
}
/*
void Sensors::updateTachometers()
{
	unsigned int cur_shooter_wheel_count = shooter_wheel_tach->Get();
	float cycle_time = getCycleTime();

	// multiply by 60 to convert to RPM
	shooter_wheel_tach_rate = (float)(cur_shooter_wheel_count - prev_shooter_wheel_tach_count) / cycle_time * 60.0;

	prev_shooter_wheel_tach_count = cur_shooter_wheel_count;
}
*/

float Sensors::getCycleTime()
{
	return cycle_timer->Get() - prev_time_stamp;
}

void Sensors::updateCycleTime()
{
	prev_time_stamp = cycle_timer->Get();
}
