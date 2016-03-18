#ifndef MaintainShooterAngle_H
#define MaintainShooterAngle_H

#include "../CommandBase.h"
#include "WPILib.h"

class MaintainShooterAngle: public CommandBase
{
public:
	MaintainShooterAngle();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	static const float UNKNOWN_ANGLE_POWER;
	static const float ANGLE_POWER_SCALE1;
	static const float ANGLE_POWER_SCALE2;
	static const float POWER_SCALE_FENCE;

};

#endif
