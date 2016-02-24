#ifndef SetShooterPitch_H
#define SetShooterPitch_H

#include "../CommandBase.h"
#include "WPILib.h"

class SetShooterPitch: public CommandBase
{
public:
	//Angle in degrees
	SetShooterPitch(float, float);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	static const float TIMEOUT;

	float pitch;
	float accepted_error;

	bool interrupted;

};

#endif
