#ifndef Shooter_H
#define Shooter_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

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

	CANTalon* left_shooter_wheel;
	CANTalon* right_shooter_wheel;
	CANTalon* pitch_angle;



};

#endif
