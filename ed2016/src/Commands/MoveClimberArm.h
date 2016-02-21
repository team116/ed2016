#ifndef MoveClimberArm_H
#define MoveClimberArm_H

#include <CommandBase.h>
#include <WPILib.h>

class MoveClimberArm: public CommandBase
{
public:
	MoveClimberArm(Climber::ClimberArmDirection direction, float speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	Climber::ClimberArmDirection direction;
	float speed;
};
#endif
