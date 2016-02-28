#ifndef MoveBackWinch_H
#define MoveBackWinch_H

#include <CommandBase.h>
#include <RobotMap.h>

class MoveBackWinch: public CommandBase
{
public:
	MoveBackWinch(Utils::VerticalDirection);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	Utils::VerticalDirection movement_direction;
};

#endif
