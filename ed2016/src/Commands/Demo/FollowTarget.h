#ifndef FollowTarget_H
#define FollowTarget_H

#include <CommandBase.h>
#include "WPILib.h"

class FollowTarget: public CommandBase
{
public:
	FollowTarget();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
