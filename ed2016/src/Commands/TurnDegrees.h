#ifndef TurnDegrees_H
#define TurnDegrees_H

#include "../CommandBase.h"
#include "WPILib.h"

/**
 * Turns a maximum of 180 degrees, taking the shortest path to its destination
 * So if given an angle like 350, it will turn -10
 */
class TurnDegrees: public CommandBase
{
public:
	TurnDegrees(float degrees, float error = 5.0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	static const float TURN_SPEED;

	float acceptable_error;
	float degrees;

	float starting_angle;
	float target_angle;

	bool interrupted;
};

#endif
