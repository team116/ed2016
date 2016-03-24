#ifndef AutoWinch_H
#define AutoWinch_H

#include "../CommandBase.h"
#include "WPILib.h"

class AutoWinch: public CommandBase
{
public:
	AutoWinch();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	bool pid_enabled;
	float target_angle;

	static const float DEGREE_TOLERANCE;
	static const float OFFSET_SPEED;
};

#endif
