#ifndef MoveHolderWheel_H
#define MoveHolderWheel_H

#include <CommandBase.h>
#include <RobotMap.h>

class MoveHolderWheel: public CommandBase
{
public:
	MoveHolderWheel(Utils::HorizontalDirection dir);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	Utils::HorizontalDirection direction;

};

#endif
