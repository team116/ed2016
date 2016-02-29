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

	static const float TARGET_HEIGHT;

public:
	enum PitchType {
		CAMERA,
		LIDAR
	};

	ShooterPitch();
	void InitDefaultCommand();

	enum ShooterPitchDirection {
		SHOOTER_UP,
		SHOOTER_STILL,
		SHOOTER_DOWN
	};

	void setShooterPitchSpeed(float speed);
	void setShooterPitchDirection(ShooterPitchDirection);
	void checkLimits();

	float getPitchToTarget(PitchType);
};

#endif
