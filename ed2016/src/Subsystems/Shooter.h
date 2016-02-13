#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
#include <RobotMap.h>
#include <WPILib.h>

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
	void checkLimits();
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities


private:
	Shooter();
	static Shooter* INSTANCE;

	MOTOR_TYPE* top_shooter_wheel;
	MOTOR_TYPE* bottom_shooter_wheel;
	MOTOR_TYPE* pitch_angle;



};

#endif
