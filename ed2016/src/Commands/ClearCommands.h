#ifndef ClearCommands_H
#define ClearCommands_H

#include <CommandBase.h>
#include <WPILib.h>

class ClearCommands: public CommandBase
{
public:
	ClearCommands();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
