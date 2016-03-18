#ifndef CheckLidar_H
#define CheckLidar_H

#include "../CommandBase.h"
#include "WPILib.h"

class UpdateSensors: public CommandBase
{
public:
	UpdateSensors();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	float distance;
	bool lidar_read;
};

#endif
