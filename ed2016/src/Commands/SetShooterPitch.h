#ifndef SetShooterPitch_H
#define SetShooterPitch_H

#include "../CommandBase.h"
#include "WPILib.h"

class SetShooterPitch: public CommandBase
{
public:
	SetShooterPitch(float, float);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float pitch;
	float accepted_error;

	bool interrupted;

};

#endif
