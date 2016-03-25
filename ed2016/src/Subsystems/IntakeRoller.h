#ifndef IntakeRoller_H
#define IntakeRoller_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <RobotMap.h>

class IntakeRoller: public Subsystem
{
public:
	IntakeRoller();
	void InitDefaultCommand();

	void setDirection(Utils::HorizontalDirection dir);

private:
	static const float ROLLER_SPEED;

	SpeedController* roller;

	Utils::HorizontalDirection direction;

};

#endif
