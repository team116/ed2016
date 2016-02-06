#ifndef SweepForGoal_H
#define SweepForGoal_H

#include <CommandBase.h>
#include <WPILib.h>

class SweepForGoal: public CommandBase
{
public:
	SweepForGoal(int); //initial position (1 through 5, with low bar on outside edge as 1)
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	int initial_position;
	float angle;
	static const float TURN_SPEED;
	bool interrupted;
};

#endif
