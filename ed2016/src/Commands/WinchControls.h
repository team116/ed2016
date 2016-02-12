#ifndef WinchControls_H
#define WinchControls_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "OI.h"

class WinchControls: public CommandBase
{
public:
	WinchControls();
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
