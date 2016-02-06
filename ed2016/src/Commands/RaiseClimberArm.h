#ifndef RaiseClimberArm_H
#define RaiseClimberArm_H

#include "../CommandBase.h"
#include "WPILib.h"

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

};

#endif
