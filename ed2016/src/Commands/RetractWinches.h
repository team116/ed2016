#ifndef RetractWinches_H
#define RetractWinches_H

#include <CommandBase.h>
#include <WPILib.h>

class RetractWinches: public CommandBase
{
public:
	RetractWinches();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool interrupted;

	Timer* temmie;

	static const float ARM_TIMEOUT;
	static const float WINCH_TIMEOUT;
};

#endif
