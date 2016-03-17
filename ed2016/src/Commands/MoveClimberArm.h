#ifndef MoveClimberArm_H
#define MoveClimberArm_H

#include <CommandBase.h>
#include <RobotMap.h>
#include <WPILib.h>

class MoveClimberArm: public CommandBase
{
public:
	MoveClimberArm(Utils::VerticalDirection);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	Utils::VerticalDirection movement_direction;
};

#endif
