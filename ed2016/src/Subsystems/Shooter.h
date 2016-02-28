#ifndef Shooter_H
#define Shooter_H

#include <Commands/PIDSubsystem.h>
#include <RobotMap.h>
#include <WPILib.h>

class Shooter: public PIDSubsystem
{
public:
	Shooter();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();

	void setShooterSpeed(float speed);
	void checkLimits();

	float getRPMPreset(int preset); // 0 to 5
	float getSpeedPreset(int preset); // 0 to 5

private:
	SpeedController* top_shooter_wheel;
	SpeedController* bottom_shooter_wheel;

	static const float RPM_PRESETS[];
	static const float SPEED_PRESETS[];

};
#endif
