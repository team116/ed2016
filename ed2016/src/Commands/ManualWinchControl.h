#ifndef ManualWinchControl_H
#define ManualWinchControl_H

#include "../CommandBase.h"
#include "WPILib.h"

class ManualWinchControl: public CommandBase
{
public:
	ManualWinchControl();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float back_winch;
	float front_winch;
};

#endif
