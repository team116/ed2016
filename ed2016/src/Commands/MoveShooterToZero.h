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
	static const float EXTRA_BACKDRIVE_TIMEOUT;

	Timer* extra_backdrive_timer;

	bool pid_was_enabled;
	bool last_switch_value;

};

#endif
