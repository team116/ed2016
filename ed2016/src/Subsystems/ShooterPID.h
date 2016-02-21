#ifndef ShooterPID_H
#define ShooterPID_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
#include <RobotMap.h>

class ShooterPID: public PIDSubsystem
{
public:
	ShooterPID();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();
	void checkLimits();

	float getRPMPreset(int preset); // 0 to 5
	float getSpeedPreset(int preset); // 0 to 5
private:
	MOTOR_TYPE* top_shooter_wheel;
	MOTOR_TYPE* bottom_shooter_wheel;

	static const float RPM_PRESETS[];
	static const float SPEED_PRESETS[];
};

#endif
