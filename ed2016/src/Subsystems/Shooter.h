#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
#include <RobotMap.h>
#include <WPILib.h>


// included shooter
class Shooter: public Subsystem
{
public:
	Shooter();
	void InitDefaultCommand();

	void setShooterSpeed(float speed);

	float getRPMPreset(int preset); // 0 to 5
	float getSpeedPreset(int preset); // 0 to 5

	float getSpeedToTarget(float angle);

private:
	SpeedController* shooter_wheel;

	static const float RPM_PRESETS[];
	static const float SPEED_PRESETS[];

};

#endif
