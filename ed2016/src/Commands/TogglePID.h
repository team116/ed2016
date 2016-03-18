#ifndef TogglePID_H
#define TogglePID_H

#include "../CommandBase.h"
#include "WPILib.h"

class TogglePID: public CommandBase
{
public:
	TogglePID(bool);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	bool use_pid;
	bool finished;
};

#endif
