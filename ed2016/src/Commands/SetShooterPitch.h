#ifndef SetShooterPitch_H
#define SetShooterPitch_H

#include "../CommandBase.h"
#include "WPILib.h"

#include <Subsystems/ShooterPitch.h>

class SetShooterPitch: public CommandBase
{
public:
	static const float DEFAULT_ACCEPTABLE_ERROR;
	//Angle in degrees
	SetShooterPitch(float angle, bool use_pid, float error = DEFAULT_ACCEPTABLE_ERROR);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	static void zeroTimedAngleTracker();

private:
	static const float TIMEOUT;

	float pitch;
	float accepted_error;

	bool interrupted;

	bool pid_mode;

	static float last_angle;

};

#endif
