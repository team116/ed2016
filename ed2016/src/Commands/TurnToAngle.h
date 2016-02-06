#ifndef TurnToAngle_H
#define TurnToAngle_H

#include "../CommandBase.h"
#include "WPILib.h"

class TurnToAngle: public CommandBase
{
public:
	TurnToAngle(float, float err = 3);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float target_angle;
	float angle;
	float error;
	bool interrupted;

	static const float TURN_SPEED;
};

#endif
