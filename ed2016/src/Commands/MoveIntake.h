#ifndef MoveIntake_H
#define MoveIntake_H

#include <CommandBase.h>
#include <WPILib.h>

class MoveIntake: public CommandBase
{
public:
	MoveIntake(Intake::IntakeDirection direction);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	Intake::IntakeDirection direction;
};

#endif
