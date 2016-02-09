#ifndef HolderWheel_H
#define HolderWheel_H

#include "Commands/Subsystem.h"
#include <RobotMap.h>
#include "WPILib.h"

class HolderWheel: public Subsystem
{
public:
	static HolderWheel* getInstance();
	void turnHolderWheelOn(bool);
private:
	HolderWheel();
	void InitDefaultCommand();
	static HolderWheel* INSTANCE;

	MOTOR_TYPE* holder_wheel;
};

#endif
