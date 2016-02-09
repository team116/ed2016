#ifndef PushFrontClimberWinch_H
#define PushFrontClimberWinch_H

#include "../CommandBase.h"
#include "WPILib.h"

class PushFrontClimberWinch: public CommandBase
{
public:
	PushFrontClimberWinch();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
