#ifndef LowerIntake_H
#define LowerIntake_H

#include "../CommandBase.h"
#include "WPILib.h"

class LowerIntake: public CommandBase
{
public:
	LowerIntake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
