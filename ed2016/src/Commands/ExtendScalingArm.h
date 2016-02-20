#ifndef ExtendScalingArm_H
#define ExtendScalingArm_H

#include <CommandBase.h>
#include <WPILib.h>

class ExtendScalingArm: public CommandBase
{
public:
	ExtendScalingArm();
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

	static const float SHOOTER_ERROR;
};

#endif
