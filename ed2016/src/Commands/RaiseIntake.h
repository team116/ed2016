#ifndef RaiseIntake_H
#define RaiseIntake_H

#include "../CommandBase.h"
#include "WPILib.h"

class RaiseIntake: public CommandBase
{
public:
	RaiseIntake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
