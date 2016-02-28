#ifndef MoveIntakeAngle_H
#define MoveIntakeAngle_H

#include <CommandBase.h>
#include <RobotMap.h>

class MoveIntakeAngle: public CommandBase
{
public:
	MoveIntakeAngle(Utils::VerticalDirection);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	Utils::VerticalDirection movement_direction;
};

#endif
