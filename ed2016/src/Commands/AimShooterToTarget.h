#ifndef AimShooterToTarget_H
#define AimShooterToTarget_H

#include "../CommandBase.h"
#include "WPILib.h"

class AimShooterToTarget: public CommandBase
{
public:
	AimShooterToTarget();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float pitch;
	float rpm;
	float current_pitch;

	bool interrupted;
};

#endif
