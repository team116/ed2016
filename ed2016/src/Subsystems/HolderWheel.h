#ifndef HolderWheel_H
#define HolderWheel_H

#include "Commands/Subsystem.h"
#include <RobotMap.h>
#include "WPILib.h"

class HolderWheel: public Subsystem
{
public:
	enum HolderWheelDirection
		{
			WHEEL_IN,
			WHEEL_OUT,
			WHEEL_STILL
		};
	static HolderWheel* getInstance();
	void holderWheelDirection(HolderWheelDirection direction);

private:
	HolderWheel();
	void InitDefaultCommand();
	static HolderWheel* INSTANCE;

	MOTOR_TYPE* holder_wheel;
};

#endif
