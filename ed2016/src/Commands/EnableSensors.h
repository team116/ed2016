#ifndef EnableSensors_H
#define EnableSensors_H

#include <CommandBase.h>
#include <WPILib.h>

class EnableSensors: public CommandBase
{
public:
	EnableSensors(bool enable);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	bool enable;

};

#endif
