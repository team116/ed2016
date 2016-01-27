#ifndef Sensors_H
#define Sensors_H

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
	float lidarDistance();



private:
	Sensors();
	static Sensors* INSTANCE;

	static const float SHOOTER_ANGLE_OFFSET;
	AnalogInput* shooter_angle_encoder;

	static const float INTAKE_ANGLE_OFFSET;
	AnalogInput*  intake_angle_encoder;

};

#endif
