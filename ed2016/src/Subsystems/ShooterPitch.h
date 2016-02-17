#ifndef ShooterPitch_H
#define ShooterPitch_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <RobotMap.h>
#include <Subsystems/Sensors.h>

class ShooterPitch: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	MOTOR_TYPE* pitch_angle;
	Sensors* sensors;

	static ShooterPitch* INSTANCE;

public:
	ShooterPitch();
	void InitDefaultCommand();

	static ShooterPitch* getInstance();

	enum ShooterPitchDirection {
		SHOOTER_UP,
		SHOOTER_STILL,
		SHOOTER_DOWN
	};

	void setShooterPitchDirection(ShooterPitchDirection);
	void checkLimits();
};

#endif
