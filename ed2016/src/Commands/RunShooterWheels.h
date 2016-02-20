#ifndef RunShooterWheels_H
#define RunShooterWheels_H

#include "../CommandBase.h"
#include "WPILib.h"

class RunShooterWheels: public CommandBase
{
public:
	RunShooterWheels();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
