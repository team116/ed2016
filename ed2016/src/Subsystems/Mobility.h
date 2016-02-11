#ifndef Mobility_H
#define Mobility_H

#include <Commands/Subsystem.h>
#include <RobotMap.h>
#include <WPILib.h>

class Mobility: public Subsystem
{
public:
	void InitDefaultCommand();
	static Mobility* getInstance();

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	void setLeft(float speed);
	void setRight(float speed);
	void setStraight(float speed);

	void useFrontOrientation(bool front);

	PIDOutput* getPIDOutputLeft();
	PIDOutput* getPIDOutputRight();

private:
	Mobility();
	static Mobility* INSTANCE;
	MOTOR_TYPE* leftFront;
	MOTOR_TYPE* leftBack;
	MOTOR_TYPE* rightFront;
	MOTOR_TYPE* rightBack;

	bool front_orientation;

};

#endif
