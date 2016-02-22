#ifndef HolderWheel_H
#define HolderWheel_H

#include "Commands/Subsystem.h"
#include <RobotMap.h>
#include "WPILib.h"

class HolderWheel: public Subsystem
{
public:
	HolderWheel();
	void setWheelDirection(Utils::HorizontalDirection direction);
	Utils::HorizontalDirection getWheelDirection();

private:
	void InitDefaultCommand();

	MOTOR_TYPE* holder_wheel;

	Utils::HorizontalDirection wheel_direction;
};

#endif
