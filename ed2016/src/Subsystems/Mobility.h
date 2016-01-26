#ifndef Mobility_H
#define Mobility_H

#include <Commands/Subsystem.h>
#include <WPILib.h>

class Mobility: public Subsystem
{
public:
	void InitDefaultCommand();
	static Mobility* getInstance();

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	void SetLeft(float speed);
	void SetRight(float speed);
	void SetStraight(float speed);

	void useFrontOrientation(bool front);

private:
	Mobility();
	static Mobility* INSTANCE;
	CANTalon* leftFront;
	CANTalon* leftBack;
	CANTalon* rightFront;
	CANTalon* rightBack;

	bool front_orientation;

};

#endif
