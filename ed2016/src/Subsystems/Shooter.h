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

	enum ShooterPitchDirection
	{
		SHOOTER_UP,
		SHOOTER_STILL,
		SHOOTER_DOWN
	};

	void setShooterSpeed(float speed);
	void setShooterPitchDirection(ShooterPitchDirection);
	void checkLimits();

	float getRPMPreset(int preset); // 0 to 5
	float getSpeedPreset(int preset); // 0 to 5

private:
	MOTOR_TYPE* top_shooter_wheel;
	MOTOR_TYPE* bottom_shooter_wheel;
	MOTOR_TYPE* pitch_angle;

	static const float RPM_PRESETS[];
	static const float SPEED_PRESETS[];

};

#endif
