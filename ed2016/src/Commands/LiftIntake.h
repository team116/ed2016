#ifndef LiftIntake_H
#define LiftIntake_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <RobotMap.h>

class LiftIntake: public CommandBase
{
public:
	LiftIntake(Utils::VerticalDirection dir);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	Utils::VerticalDirection direction;

	bool pid_enabled;

};

#endif
