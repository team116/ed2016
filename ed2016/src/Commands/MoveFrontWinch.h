#ifndef MoveFrontWinch_H
#define MoveFrontWinch_H

#include <CommandBase.h>
#include <RobotMap.h>

class MoveFrontWinch: public CommandBase
{
public:
	MoveFrontWinch(Utils::VerticalDirection);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	Utils::VerticalDirection movement_direction;
};

#endif
