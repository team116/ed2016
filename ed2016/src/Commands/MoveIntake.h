#ifndef MoveIntake_H
#define MoveIntake_H

#include <CommandBase.h>
#include <RobotMap.h>

class MoveIntake: public CommandBase
{
public:
	MoveIntake(Utils::HorizontalDirection direction);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	Utils::HorizontalDirection direction;
};

#endif
