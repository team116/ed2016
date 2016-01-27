#ifndef Shooter_H
#define Shooter_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

// included shooter & intake
class Shooter: public Subsystem
{
public:
	static Shooter* getInstance();
	void InitDefaultCommand();
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	enum IntakeDirection
	{
		INTAKE_IN,
		INTAKE_STILL,
		INTAKE_OUT
	};
	void setIntakeDirection(IntakeDirection value);
private:
	Shooter();
	static Shooter* INSTANCE;

	CANTalon* intake_roller;
	CANTalon* left_shooter_wheel;
	CANTalon* right_shooter_wheel;

	enum ShooterDirection
	{
		SHOOT_OUT,
		SHOOT_STILL,
		SHOOT_IN
	};
	void setShooterDirection(ShooterDirection value);
};

#endif