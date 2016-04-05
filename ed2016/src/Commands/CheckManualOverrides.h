#ifndef CheckManualOverrides_H
#define CheckManualOverrides_H

#include <CommandBase.h>
#include <WPILib.h>

class CheckManualOverrides: public CommandBase
{
public:
	CheckManualOverrides();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	static const float MIN_PID_TOGGLE_TIME;
	Timer* pid_toggle_timer;

	void checkPIDOverrideTimed(bool enable);

};

#endif
