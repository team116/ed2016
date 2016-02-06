#ifndef PushClimberWinch_H
#define PushClimberWinch_H

#include "../CommandBase.h"
#include "WPILib.h"

class PushClimberWinch: public CommandBase
{
public:
	PushClimberWinch();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
