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
	static const float ACCEPTED_LIDAR_ERROR;

	float pitch;
	float distance;
	float rpm;
	float current_pitch;

	bool interrupted;
};

#endif
