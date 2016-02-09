#ifndef PullFrontClimberWinch_H
#define PullFrontClimberWinch_H

#include <CommandBase.h>
#include <WPILib.h>

class PullFrontClimberWinch: public CommandBase
{
public:
	PullFrontClimberWinch();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
