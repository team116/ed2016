#ifndef LowerShooterToZero_H
#define LowerShooterToZero_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <Subsystems/ShooterPitch.h>
class LowerShooterToZero: public CommandBase
{
public:
	LowerShooterToZero();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool was_pid_enabled;
};

#endif
