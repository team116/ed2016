#include <Commands/UpdateSensors.h>
#include <Subsystems/Sensors.h>
#include <RobotMap.h>
#include <WPILib.h>
#include <NAVX/AHRS.h>

// get access to pi const: M_PI
#define _USE_MATH_DEFINES
#include <math.h>

const float Sensors::MIN_SHOOTER_ANGLE_VOLT = 1.42;
const float Sensors::MAX_SHOOTER_ANGLE_VOLT = 2.62;

const float Sensors::MIN_INTAKE_ANGLE_VOLT = 2.5;		//min value measured from
const float Sensors::MAX_INTAKE_ANGLE_VOLT = 3.72;		//max value measured from

const float Sensors::INTAKE_VOLT_ADJUSTMENT = 2.5;

const float Sensors::DRIVE_WHEEL_DIAMETER = 7.9502;
const int Sensors::DRIVE_WHEEL_PPR = 128;

const int Sensors::SHOOTER_WHEEL_PPR = 1;

const int Sensors::LIDAR_OFFSET = 10;

const bool Sensors::DRIVE_ENCODERS_ENABLED = false;
const bool Sensors::LIDAR_SENSOR_ENABLED = true;
const bool Sensors::SHOOTER_ANGLE_ENABLED = true;
const bool Sensors::ROBOT_ANGLE_ENABLED = true;
const bool Sensors::INTAKE_ANGLE_ENABLED = true;
const bool Sensors::BALL_SWITCH_ENABLED = true;
const bool Sensors::SHOOTER_HOME_SWITCH_ENABLED = true;
const bool Sensors::SHOOTER_WHEEL_TACHOMETER_ENABLED = true;

// objects need to be initialized to null so that they don't try to use resources that haven't been set up statically
Timer* Sensors::tach_pulse_timer = nullptr;
int Sensors::last_tach_count = 0;
float Sensors::last_tach_timestamp = 0.0;
bool Sensors::continue_sensor_update_thread = true;
mutex* Sensors::tach_speed_access = nullptr;
Counter* Sensors::shooter_wheel_tach = nullptr;
float Sensors::shooter_wheel_tach_rate = 0.0;

Sensors::Sensors() : Subsystem("Sensors") // constructor for sensors
{
	log = Log::getInstance();

	tach_pulse_timer = new Timer();
	tach_speed_access = new mutex();
	shooter_wheel_tach = new Counter(RobotPorts::SHOOTER_WHEEL_TACH);

	shooter_angle_offset = 0.0;
	shooter_angle_encoder = new AnalogInput(RobotPorts::SHOOTER_ANGLE_ENCODER);

	shooter_angle_offset = 0.0;
	intake_angle_encoder = new AnalogInput(RobotPorts::INTAKE_ANGLE_ENCODER);
	shooter_home_switch = new DigitalInput(RobotPorts::SHOOTER_HOME_SWITCH);

	//shooter_wheel_tach = new Counter(RobotPorts::SHOOTER_WHEEL_TACH);
	//top_shooter_wheel_tach = new Counter(RobotPorts::TOP_SHOOTER_WHEEL_TACH);
	//bottom_shooter_wheel_tach = new Counter(RobotPorts::BOTTOM_SHOOTER_WHEEL_TACH);

	shooter_wheel_tach->ClearDownSource();
	//shooter_wheel_tach_rate = 0.0;
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
	lidar = new I2C(I2C::Port::kMXP, RobotPorts::LIDAR_ADDRESS);

	navx = new AHRS(SPI::Port::kMXP);

	pdp = new PowerDistributionPanel(RobotPorts::PDP);

	drive_encoders_soft_enabled = true;
	lidar_sensor_soft_enabled = true;
	shooter_angle_soft_enabled = true;
	robot_angle_soft_enabled = true;
	intake_angle_soft_enabled = true;
	ball_switch_soft_enabled = true;
	shooter_home_switch_soft_enabled = true;
	shooter_wheel_tachometer_soft_enabled = true;

	if (isShooterWheelTachometerEnabled())
	{
		tach_pulse_timer->Start();
		tach_pulse_timer->Reset();
		sensor_update_thread = new thread(updateSensorsThread);
		sensor_update_thread->detach(); // let the thread run separately
	}
	else
	{
		sensor_update_thread = nullptr;
		continue_sensor_update_thread = false;
	}
}

Sensors::~Sensors()
{
	continue_sensor_update_thread = false;
	if (sensor_update_thread != nullptr)
	{
		sensor_update_thread->join();
		delete sensor_update_thread;
	}
}

void Sensors::InitDefaultCommand()
{
	SetDefaultCommand(new UpdateSensors());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Sensors::zeroShooterPitch()
{
	float actual = shooterAngleActual();
	/*
	char text[255];
	snprintf(text, 255, "Zeroing shooter angle to %f", actual);
	DriverStation::ReportError(text);
	*/
	shooter_angle_offset = actual;
}

float Sensors::shooterAngleActual()
{
	return 90.0 * (shooter_angle_encoder->GetVoltage() - MIN_SHOOTER_ANGLE_VOLT) / (MAX_SHOOTER_ANGLE_VOLT - MIN_SHOOTER_ANGLE_VOLT);
}

float Sensors::shooterAngle()
{
	if (isShooterAngleEnabled())
	{
		float actual = shooterAngleActual();
		/*
		char text[255];
		snprintf(text, 255, "retrieving shooter angle w/ offset: %f", shooter_angle_offset);
		DriverStation::ReportError(text);
		*/
		if (actual > 270.0)
		{
			return -(360.0 - (actual - shooter_angle_offset));
		}
		else
		{
			return actual - shooter_angle_offset;
		}
	}
	else
	{
		return 0.0;
	}
}

float Sensors::intakeVoltage()
{
	return intake_angle_encoder->GetVoltage();
}

float Sensors::shooterVoltage()
{
	return shooter_angle_encoder->GetVoltage();
}

float Sensors::robotAngle()
{
	if(isRobotAngleEnabled())
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

float Sensors::robotPitch()
{
	if(isRobotAngleEnabled())
	{
		if (Utils::getRobotType() == Utils::CAN_MOTOR_BOT)
		{
			return navx->GetPitch();
		}
		else if (Utils::getRobotType() == Utils::ED2016_BOT)
		{
			return navx->GetPitch();
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
		if (isShooterWheelTachometerEnabled())
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
	if (isIntakeAngleEnabled())
	{
		float voltage = intake_angle_encoder->GetVoltage() + INTAKE_VOLT_ADJUSTMENT;
		voltage = Utils::wrap(voltage, 0.0, 5.0);
		voltage = 5.0 - voltage;
		return 90.0 * (voltage - (MIN_INTAKE_ANGLE_VOLT)) / (MAX_INTAKE_ANGLE_VOLT - MIN_INTAKE_ANGLE_VOLT);
	}
	else
	{
		return 0.0;
	}
}

int Sensors::lidarDistance()
{
	if (isLidarEnabled())
	{
		return lidar_distance - LIDAR_OFFSET;
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
			lidar_distance = ((buffer[0] << 8) + buffer[1]);
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
	if (areDriveEncodersEnabled())
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
	if(areDriveEncodersEnabled())

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

void Sensors::enableDriveEncoders(bool enable)
{
	drive_encoders_soft_enabled = enable;
}

void Sensors::enableLidar(bool enable)
{
	lidar_sensor_soft_enabled = enable;
}

void Sensors::enableShooterAngle(bool enable)
{
	shooter_angle_soft_enabled = enable;
}

void Sensors::enableRobotAngle(bool enable)
{
	robot_angle_soft_enabled = enable;
}

void Sensors::enableIntakeAngle(bool disable)
{
	intake_angle_soft_enabled = disable;
}

void Sensors::enableShooterHomeSwitch(bool enable)
{
	shooter_home_switch_soft_enabled = enable;
}

void Sensors::enableShooterWheelTachometer(bool enable)
{
	shooter_wheel_tachometer_soft_enabled = enable;
}

void Sensors::enableBallSwitch(bool enable)
{
	ball_switch_soft_enabled = enable;
}

bool Sensors::areDriveEncodersEnabled()
{
	return DRIVE_ENCODERS_ENABLED && drive_encoders_soft_enabled;
}

bool Sensors::isLidarEnabled()
{
	return LIDAR_SENSOR_ENABLED && lidar_sensor_soft_enabled;
}

bool Sensors::isShooterAngleEnabled()
{
	return SHOOTER_ANGLE_ENABLED && shooter_angle_soft_enabled;
}

bool Sensors::isRobotAngleEnabled()
{
	return ROBOT_ANGLE_ENABLED && robot_angle_soft_enabled;
}

bool Sensors::isIntakeAngleEnabled()
{
	return INTAKE_ANGLE_ENABLED && intake_angle_soft_enabled;
}

bool Sensors::isShooterHomeSwitchEnabled()
{
	return SHOOTER_HOME_SWITCH_ENABLED && shooter_home_switch_soft_enabled;
}

bool Sensors::isShooterWheelTachometerEnabled()
{
	return SHOOTER_WHEEL_TACHOMETER_ENABLED && shooter_wheel_tachometer_soft_enabled;
}

bool Sensors::isBallSwitchEnabled()
{
	return BALL_SWITCH_ENABLED && ball_switch_soft_enabled;
}

bool Sensors::getBallSwitch()
{
	if (isBallSwitchEnabled())
	{
		return getBallSwitchActual();
	}
	else
	{
		return false;
	}
}

bool Sensors::getBallSwitchActual()
{
	return !ready_to_shoot_balls_switch->Get();
}

float Sensors::getCurrent(unsigned int port)
{
	return pdp->GetCurrent(port);
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
	if (areDriveEncodersEnabled())
	{
		return left_drive_encoder->GetRate();
	}
	return 0.0;
}

float Sensors::getSpeedRight()
{
	if (areDriveEncodersEnabled())
	{
		return right_drive_encoder->GetRate();
	}
	return 0.0;
}

float Sensors::getCycleTime()
{
	return cycle_timer->Get() - prev_time_stamp;
}

void Sensors::updateCycleTime()
{
	prev_time_stamp = cycle_timer->Get();
}

void Sensors::updateSensorsThread()
{
	float timestamp;
	while (continue_sensor_update_thread)
	{
		timestamp = tach_pulse_timer->Get();
		if (shooter_wheel_tach->Get() > last_tach_count)
		{
			int count = shooter_wheel_tach->Get();
			setShooterSpeedTachValue((float)(count - last_tach_count) / (timestamp - last_tach_timestamp) / (float)SHOOTER_WHEEL_PPR * 60.0);

			last_tach_count = count;
			last_tach_timestamp = timestamp;
		}
		else if (timestamp - last_tach_timestamp > 1.0)
		{
			setShooterSpeedTachValue(0.0);
		}
	}
}

void Sensors::setShooterSpeedTachValue(float rate)
{
	lock_guard<mutex> guard(*tach_speed_access);
	shooter_wheel_tach_rate = rate;
}
