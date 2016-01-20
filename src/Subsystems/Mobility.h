#ifndef Mobility_H
#define Mobility_H

#include <Commands/Subsystem.h>
#include <WPILib.h>

class Mobility: public Subsystem
{
public:
	void InitDefaultCommand();
	static Mobility* getInstance();
	void SetLeft();
	void SetRight();
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

private:
	Mobility();
	static Mobility* INSTANCE;
	CANTalon* leftFront;
	CANTalon* leftBack;
	CANTalon* rightFront;
	CANTalon* rightBack;


};

#endif
