#ifndef ProcessVision_H
#define ProcessVision_H

#include "../CommandBase.h"
#include "WPILib.h"

class ProcessVision: public CommandBase
{
public:
	ProcessVision();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	std::shared_ptr<NetworkTable> table;
};

#endif
