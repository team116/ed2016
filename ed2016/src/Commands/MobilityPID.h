#ifndef MobilityPID_H
#define MobilityPID_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <PIDController.h>

class MobilityPID: public CommandBase
{
public:
	MobilityPID();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	PIDController* left_shark;
	PIDController* right_shark;


	static const float P_VAL;
	static const float I_VAL;
	static const float D_VAL;

	bool interrupted;
};

#endif
