#ifndef ShooterPitch_H
#define ShooterPitch_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <RobotMap.h>

class ShooterPitch: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	SpeedController* pitch_angle;

public:
	ShooterPitch();
	void InitDefaultCommand();

	enum ShooterPitchDirection {
		SHOOTER_UP,
		SHOOTER_STILL,
		SHOOTER_DOWN
	};

	void setShooterPitchDirection(ShooterPitchDirection);
	void checkLimits();
};

#endif
