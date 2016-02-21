#ifndef LowerClimberArm_H
#define LowerClimberArm_H

#include <CommandBase.h>
#include <WPILib.h>

class LowerClimberArm: public CommandBase
{
public:
	LowerClimberArm();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:

};

#endif
