#ifndef PullBackClimberWinch_H
#define PullBackClimberWinch_H

#include "../CommandBase.h"
#include "WPILib.h"

class PullBackClimberWinch: public CommandBase
{
public:
	PullBackClimberWinch();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
