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
	float getLeft();
	float getRight();

	void useFrontOrientation(bool front);

private:
	SpeedController* leftFront;
	SpeedController* leftBack;
	SpeedController* rightFront;
	SpeedController* rightBack;

	bool front_orientation;

};

#endif
