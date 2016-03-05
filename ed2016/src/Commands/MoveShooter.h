#ifndef MoveShooter_H
#define MoveShooter_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <RobotMap.h>

class MoveShooter: public CommandBase
{
public:
	MoveShooter(Utils::VerticalDirection dir);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	Utils::VerticalDirection direction;

};

#endif
