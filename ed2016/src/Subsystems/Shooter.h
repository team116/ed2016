#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
#include <RobotMap.h>
#include <WPILib.h>
#include <Subsystems/Sensors.h>

// included shooter
class Shooter: public Subsystem
{
public:
	static Shooter* getInstance();

	void InitDefaultCommand();
	void turnShooterOn(bool);
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities


private:
	Shooter();
	static Shooter* INSTANCE;

	MOTOR_TYPE* top_shooter_wheel;
	MOTOR_TYPE* bottom_shooter_wheel;

	Sensors* sensors;

};

#endif
