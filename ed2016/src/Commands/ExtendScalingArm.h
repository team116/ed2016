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
	bool shooter_ready;
	Timer* temmie;
	Timer* temmie_sp; //shooter pitch tem

	static const float TIMEOUT_1;
	static const float TIMEOUT_2;
	static const float SHOOTER_TIMEOUT;

	static const float SPEED_1;
	static const float SPEED_2;

	static const float SHOOTER_ERROR;
};

#endif
