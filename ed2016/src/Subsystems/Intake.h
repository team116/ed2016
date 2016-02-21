#ifndef Yellow_H
#define Yellow_H

#include <Commands/Subsystem.h>
#include <RobotMap.h>
#include <WPILib.h>

class Intake: public Subsystem
{
public:
	Intake();
	void InitDefaultCommand();
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	void setIntakeDirection(Utils::HorizontalDirection);
	void setIntakeAngleDirection(Utils::VerticalDirection);

private:
	SpeedController* intake_roller;
	SpeedController* intake_angle;

};

#endif
