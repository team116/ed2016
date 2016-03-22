#ifndef TurnToTarget_H
#define TurnToTarget_H

#include "../CommandBase.h"
#include "WPILib.h"

class TurnToTarget: public CommandBase
{
public:
	TurnToTarget();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float pixels_off;
};

#endif
