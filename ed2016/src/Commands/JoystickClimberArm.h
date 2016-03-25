#ifndef JoystickClimberArm_H
#define JoystickClimberArm_H

#include "../CommandBase.h"
#include "WPILib.h"

class JoystickClimberArm: public CommandBase
{
public:
	JoystickClimberArm();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
