#ifndef SetShooterWheels_H
#define SetShooterWheels_H

#include "../CommandBase.h"
#include "WPILib.h"

class SetShooterWheels: public CommandBase
{
public:
	SetShooterWheels(float rpm);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float setpoint;
};

#endif
