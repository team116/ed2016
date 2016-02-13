#ifndef Sensors_H
#define Sensors_H

#include <NAVX/AHRS.h>
#include <Commands/Subsystem.h>
#include <WPILib.h>

class Sensors: public Subsystem
{
public:
	void InitDefaultCommand();
	static Sensors* getInstance();
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	bool isReadyToShoot(); // Limit Switch
	float shooterAngle();	//read the encoder
	float robotAngle();
	//a method to read the LIDAR, the return type of which we do not yet know
	float speedLeftShooterWheel();
	float speedRightShooterWheel();
	float intakeAngle();
	int lidarDistance();
	void refreshLidar();
	float getDistanceLeft();
	float getDistanceRight();
	float getSpeedLeft();
	float getSpeedRight();
	void resetEncoderLeft();
	void resetEncoderRight();
	bool areDriveEncoderEnabled();
	bool areLidarEnabled();
	bool areShooterAngleEnabled();
	bool areRobotAngleEnabled();
	bool areIntakeAngleEnabled();
	bool readyToShoot();
	bool shooterWheelTachometerEnabled();

	bool isShooterHomeSwitchHorizontal();

private:
	Sensors();
	static Sensors* INSTANCE;

	static const float SHOOTER_ANGLE_OFFSET;
	AnalogInput* shooter_angle_encoder;

	static const float INTAKE_ANGLE_OFFSET;
	AnalogInput*  intake_angle_encoder;

	static const int SHOOTER_WHEEL_PPR; // pulses per revolution
	DigitalInput* left_shooter_wheel_tach_input;
	DigitalInput* right_shooter_wheel_tach_input;
	Encoder* left_shooter_wheel_tach;
	Encoder* right_shooter_wheel_tach;

	static const float DRIVE_WHEEL_DIAMETER; // inches
	static const int DRIVE_WHEEL_PPR;
	Encoder* left_drive_encoder;
	Encoder* right_drive_encoder;

	static const float WINCH_SPEED;

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

	DigitalInput* shooter_home_switch;


};

#endif
