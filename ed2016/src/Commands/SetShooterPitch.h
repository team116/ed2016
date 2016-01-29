#ifndef SetShooterPitch_H
#define SetShooterPitch_H

#include <../CommandBase.h>
#include <WPILib.h>

class SetShooterPitch: public CommandBase
{
public:
	SetShooterPitch(float);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float pitch;
};

#endif
