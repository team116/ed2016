#ifndef Shooter_H
#define Shooter_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

// included shooter
class Shooter: public Subsystem
{
public:
	static Shooter* getInstance();

	enum ShooterPitchDirection {
		SHOOTER_UP,
		SHOOTER_STILL,
		SHOOTER_DOWN
	};
	void InitDefaultCommand();
	void turnShooterOn(bool);
	void setShooterPitchDirection(ShooterPitchDirection);
	void turnPushWheelOn(bool);
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities


private:
	Shooter();
	static Shooter* INSTANCE;

	VictorSP* left_shooter_wheel;
	VictorSP* right_shooter_wheel;
	VictorSP* push_wheel;
	VictorSP* pitch_angle;



};

#endif
