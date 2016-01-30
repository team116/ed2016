#ifndef DriveDistance_H
#define DriveDistance_H

#include "../CommandBase.h"
#include "WPILib.h"


class DriveDistance: public CommandBase
{
public:
	DriveDistance(float);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	float distance;
	float starting_distance;
	float current_distance;
	int dir;

	bool interrupted;


};

#endif
