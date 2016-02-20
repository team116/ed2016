#ifndef RaiseClimberArm_H
#define RaiseClimberArm_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <Timer.h>

class RaiseClimberArm: public CommandBase
{
public:
	RaiseClimberArm();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	Timer* temmie;

};

#endif
