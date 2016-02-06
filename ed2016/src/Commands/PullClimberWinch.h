#ifndef OperateClimberWinch_H
#define OperateClimberWinch_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <Subsystems/Climber.h>

class OperateClimberWinch: public CommandBase
{
public:
	OperateClimberWinch(Climber::WinchDirection);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	Climber::WinchDirection winch_direction;
};

#endif
