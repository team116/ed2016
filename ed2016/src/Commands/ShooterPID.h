#ifndef ShooterPID_H
#define ShooterPID_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShooterPID: public CommandBase
{
public:
	ShooterPID();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	PIDController* shootPID;

	static const float P_VAL;
	static const float I_VAL;
	static const float D_VAL;

	bool interrupted;
};

#endif
