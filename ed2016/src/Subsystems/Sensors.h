#ifndef Sensors_H
#define Sensors_H

#include <NAVX/AHRS.h>
#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <Counter.h>
#include <Log.h>
#include <thread>
#include <mutex>

using namespace std;

class Sensors: public Subsystem
{
public:
	Sensors();
	~Sensors();
	void InitDefaultCommand();
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	float shooterAngle();

	float robotAngle();
	float robotPitch();

	float intakeAngle();

	float shooterVoltage();
	float intakeVoltage();

	int lidarDistance();
	void refreshLidar();

	float getCycleTime();
	void updateCycleTime();

	float speedShooterWheel();

	float getDistanceLeft();
	float getDistanceRight();
	float getSpeedLeft();
	float getSpeedRight();
	void resetEncoderLeft();
	void resetEncoderRight();

	bool readyToShoot();
	bool isShooterHomeSwitchHorizontal();

	float getCurrent(unsigned int port);

	void enableDriveEncoders(bool enable);
	void enableLidar(bool enable);
	void enableShooterAngle(bool enable);
	void enableRobotAngle(bool enable);
	void enableIntakeAngle(bool enable);
	void enableShooterHomeSwitch(bool enable);
	void enableShooterWheelTachometer(bool enable);
	void enableBallSwitch(bool enable);

	bool areDriveEncodersEnabled();
	bool isLidarEnabled();
	bool isShooterAngleEnabled();
	bool isRobotAngleEnabled();
	bool isIntakeAngleEnabled();
	bool isShooterHomeSwitchEnabled();
	bool isShooterWheelTachometerEnabled();
	bool isBallSwitchEnabled();

	void zeroShooterPitch();

private:
	Log* log;

	float shooterAngleActual();

	static Timer* tach_pulse_timer;
	static int last_tach_count;
	static float last_tach_timestamp;
	static bool continue_sensor_update_thread;
	thread* sensor_update_thread;
	static mutex* tach_speed_access;
	static void updateSensorsThread();
	static void setShooterSpeedTachValue(float rate);

	DigitalInput* ready_to_shoot_balls_switch;

	static const float MAX_SHOOTER_ANGLE_VOLT;
	static const float MIN_SHOOTER_ANGLE_VOLT;
	float shooter_angle_offset;
	AnalogInput* shooter_angle_encoder;

	static const float MIN_INTAKE_ANGLE_VOLT; // voltage @ 0 degrees
	static const float MAX_INTAKE_ANGLE_VOLT; // voltage @ 90 degrees
	static const float INTAKE_VOLT_ADJUSTMENT;

	AnalogInput*  intake_angle_encoder;

	static const int SHOOTER_WHEEL_PPR; // pulses per revolution
	static const int TACH_PERIOD_COUNT = 10;
	static Counter* shooter_wheel_tach;
	float prev_tach_timestamps[TACH_PERIOD_COUNT];
	int prev_tach_counts[TACH_PERIOD_COUNT];
	int cur_tach_period_index;
	static float shooter_wheel_tach_rate;

	Timer* cycle_timer;
	float prev_time_stamp;

	static const float DRIVE_WHEEL_DIAMETER; // inches
	static const int DRIVE_WHEEL_PPR;
	Encoder* left_drive_encoder;
	Encoder* right_drive_encoder;

	static const float WINCH_SPEED;

	static const int LIDAR_OFFSET;
	Timer* lidar_timer;
	unsigned int lidar_stage;
	I2C* lidar;
	int lidar_distance; // centimeters

	AHRS* navx;

	PowerDistributionPanel* pdp;

	static const bool DRIVE_ENCODERS_ENABLED;
	static const bool LIDAR_SENSOR_ENABLED;
	static const bool SHOOTER_ANGLE_ENABLED;
	static const bool ROBOT_ANGLE_ENABLED;
	static const bool INTAKE_ANGLE_ENABLED;
	static const bool BALL_SWITCH_ENABLED;
	static const bool SHOOTER_HOME_SWITCH_ENABLED;
	static const bool SHOOTER_WHEEL_TACHOMETER_ENABLED;

	bool drive_encoders_soft_enabled;
	bool lidar_sensor_soft_enabled;
	bool shooter_angle_soft_enabled;
	bool robot_angle_soft_enabled;
	bool intake_angle_soft_enabled;
	bool ball_switch_soft_enabled;
	bool shooter_home_switch_soft_enabled;
	bool shooter_wheel_tachometer_soft_enabled;

	DigitalInput* shooter_home_switch;

};

#endif
