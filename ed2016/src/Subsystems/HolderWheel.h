#ifndef HolderWheel_H
#define HolderWheel_H

#include "Commands/Subsystem.h"
#include <RobotMap.h>
#include "WPILib.h"

class HolderWheel: public Subsystem
{
public:
	HolderWheel();
	enum HolderWheelDirection
		{
			WHEEL_IN,
			WHEEL_OUT,
			WHEEL_STILL
		};
	void holderWheelDirection(HolderWheelDirection direction);

private:
	void InitDefaultCommand();

	MOTOR_TYPE* holder_wheel;
};

#endif
