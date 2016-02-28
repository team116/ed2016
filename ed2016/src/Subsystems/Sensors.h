#ifndef Sensors_H
#define Sensors_H

#include <NAVX/AHRS.h>
#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <Counter.h>

class Sensors: public Subsystem
{
public:
	Sensors();
	void InitDefaultCommand();
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	float shooterAngle();
	float robotAngle();
	float intakeAngle();

	int lidarDistance();
	void refreshLidar();

	float getCycleTime();
	void updateCycleTime();

	float speedTopShooterWheel();
	float speedBottomShooterWheel();
	void updateTachometers();

	float getDistanceLeft();
	float getDistanceRight();
	float getSpeedLeft();
	float getSpeedRight();
	void resetEncoderLeft();
	void resetEncoderRight();

	bool readyToShoot();
	bool isShooterHomeSwitchHorizontal();

	bool areDriveEncoderEnabled();
	bool areLidarEnabled();
	bool areShooterAngleEnabled();
	bool areRobotAngleEnabled();
	bool areIntakeAngleEnabled();
	bool shooterWheelTachometerEnabled();

private:

	static const float SHOOTER_ANGLE_OFFSET;
	AnalogInput* shooter_angle_encoder;

	static const float INTAKE_ANGLE_OFFSET;
	AnalogInput*  intake_angle_encoder;

	static const int SHOOTER_WHEEL_PPR; // pulses per revolution
	Counter* top_shooter_wheel_tach;
	Counter* bottom_shooter_wheel_tach;
	unsigned int prev_top_tach_count;
	unsigned int prev_bottom_tach_count;
	float top_tach_rate;
	float bottom_tach_rate;

	Timer* cycle_timer;
	float prev_time_stamp;

	static const float DRIVE_WHEEL_DIAMETER; // inches
	static const int DRIVE_WHEEL_PPR;
	Encoder* left_drive_encoder;
	Encoder* right_drive_encoder;

	static const float WINCH_SPEED;

	Timer* lidar_timer;
	unsigned int lidar_stage;
	I2C* lidar;
	int lidar_distance; // centimeters

	AHRS* navx;

	bool drive_encoders_enabled;
	bool lidar_sensor_enabled;
	bool shooter_angle_enabled;
	bool robot_angle_enabled;
	bool intake_angle_enabled;
	bool ready_to_shoot_enabled;
	bool shooter_wheel_tachometer_enabled;

	DigitalInput* ready_to_shoot_balls_switch;
	DigitalInput* intake_limit_switch;
	DigitalInput* shooter_home_switch;

};

#endif
