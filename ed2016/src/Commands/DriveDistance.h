#ifndef DriveDistance_H
#define DriveDistance_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <Commands/DriveStraight.h>


class DriveDistance: public CommandBase
{
public:
	DriveDistance(float);	// parameter is measured in feet
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

	static const float DRIVE_DISTANCE_TIMEOUT;

	DriveStraight* auto_drive_straight;


};

#endif
