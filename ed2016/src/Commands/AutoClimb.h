#ifndef AutoClimb_H
#define AutoClimb_H

#include "../CommandBase.h"
#include "WPILib.h"

class AutoClimb: public CommandBase
{
public:
	AutoClimb();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
