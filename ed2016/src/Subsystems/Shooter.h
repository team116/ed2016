#ifndef Shooter_H
#define Shooter_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
#include <RobotMap.h>

class Shooter: public PIDSubsystem
{
public:
	Shooter();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();

	void checkLimits();

	float getRPMPreset(int preset); // 0 to 5
	float getSpeedPreset(int preset); // 0 to 5
	void setShooterSpeed(float speed);
private:
	MOTOR_TYPE* top_shooter_wheel;
	MOTOR_TYPE* bottom_shooter_wheel;

	static const float RPM_PRESETS[];
	static const float SPEED_PRESETS[];
};

#endif
