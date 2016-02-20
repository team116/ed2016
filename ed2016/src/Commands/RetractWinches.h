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

	Timer* temmie_a;	//arm tem
	Timer* temmie_w;	//winch tem

	static const float ARM_TIMEOUT;
	static const float WINCH_TIMEOUT;
	static const float CURRENT_SPIKE_TIMEOUT;
};

#endif
