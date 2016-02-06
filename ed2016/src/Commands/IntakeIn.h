#ifndef IntakeIn_H
#define IntakeIn_H

#include "../CommandBase.h"
#include "WPILib.h"

class IntakeIn: public CommandBase
{
public:
	IntakeIn();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
