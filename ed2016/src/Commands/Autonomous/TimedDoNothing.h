#ifndef TimedDoNothing_H
#define TimedDoNothing_H

#include <CommandBase.h>
#include "WPILib.h"

class TimedDoNothing: public CommandBase
{
public:
	TimedDoNothing(float timeout);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};

#endif
