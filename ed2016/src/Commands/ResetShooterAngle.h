#ifndef ResetShooterAngle_H
#define ResetShooterAngle_H

#include "../CommandBase.h"
#include "WPILib.h"

class ResetShooterAngle: public CommandBase
{
public:
	ResetShooterAngle();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
