#ifndef PushBackClimberWinch_H
#define PushBackClimberWinch_H

#include "../CommandBase.h"
#include "WPILib.h"

class PushBackClimberWinch: public CommandBase
{
public:
	PushBackClimberWinch();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
