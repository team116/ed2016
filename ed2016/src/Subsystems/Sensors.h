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
	bool isLimitSwitched();
	float shooterAngle();	//read the encoder
	//a method to read the LIDAR, the return type of which we do not yet know



private:
	Sensors();
	static Sensors* INSTANCE;

	static const float SHOOTER_ANGLE_OFFSET;

	AnalogInput* shooter_angle_encoder;

};

#endif
