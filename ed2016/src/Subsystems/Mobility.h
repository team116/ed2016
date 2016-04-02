#ifndef Mobility_H
#define Mobility_H

#include <Commands/Subsystem.h>
#include <RobotMap.h>
#include <WPILib.h>

class Mobility: public PIDSubsystem
{
public:
	Mobility();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	void setLeft(float speed);
	void setRight(float speed);
	void setStraight(float speed);
	float getLeft();
	float getRight();

	void useFrontOrientation(bool front);

	bool isPIDEnabled();

	float getP();
	float getI();
	float getD();
	float getF();
	void setP(float);
	void setI(float);
	void setD(float);
	void setF(float);

	bool OnTarget();
	void checkTarget();

private:
	SpeedController* leftFront;
	SpeedController* leftBack;
	SpeedController* rightFront;
	SpeedController* rightBack;

	static const int CYCLES_FOR_ONTARGET;
	static const int ONTARGET_TOLERANCE;;

	bool front_orientation;

	int cycles_within_tolerance;

};

#endif
