#ifndef MoveShooterToZero_H
#define MoveShooterToZero_H

#include <CommandBase.h>
#include <WPILib.h>

class MoveShooterToZero: public CommandBase
{
public:
	MoveShooterToZero();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	bool pid_was_enabled;
};

#endif
