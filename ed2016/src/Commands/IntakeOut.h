#ifndef IntakeOut_H
#define IntakeOut_H

#include "../CommandBase.h"
#include "WPILib.h"

class IntakeOut: public CommandBase
{
public:
	IntakeOut(Intake::IntakeDirection direction);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	Intake::IntakeDirection direction;
};

#endif
