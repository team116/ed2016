#ifndef DriveByLidar_H
#define DriveByLidar_H

#include <CommandBase.h>
#include <WPILib.h>

class DriveByLidar: public CommandBase
{
public:
	//drive until the lidar is returning specified distance
	DriveByLidar(float, float);	//distance in cm, error
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float target_distance;
	float distance;
	float error;
	bool interrupted;
};

#endif
