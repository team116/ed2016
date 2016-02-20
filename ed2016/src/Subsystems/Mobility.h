#ifndef Mobility_H
#define Mobility_H

#include <Commands/Subsystem.h>
#include <RobotMap.h>
#include <WPILib.h>

class Mobility: public Subsystem
{
public:
	Mobility();
	void InitDefaultCommand();

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	void setLeft(float speed);
	void setRight(float speed);
	void setStraight(float speed);

	void useFrontOrientation(bool front);

private:
	MOTOR_TYPE* leftFront;
	MOTOR_TYPE* leftBack;
	MOTOR_TYPE* rightFront;
	MOTOR_TYPE* rightBack;

	bool front_orientation;

};

#endif
