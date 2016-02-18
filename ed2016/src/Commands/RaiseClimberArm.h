#ifndef RaiseClimberArm_H
#define RaiseClimberArm_H

#include "../CommandBase.h"
#include "WPILib.h"

class RaiseClimberArm: public CommandBase
{
public:
	RaiseClimberArm();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool interrupted;
	Timer* temmie;

	static const float TIMEOUT_1;
	static const float TIMEOUT_2;

	static const float SPEED_1;
	static const float SPEED_2;
};

#endif

