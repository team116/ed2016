#ifndef CrossDefAndShoot_H
#define CrossDefAndShoot_H

#include <Commands/CommandGroup.h>
#include <CommandBase.h>
#include <WPILib.h>
#include <Commands/Autonomous/CrossDefense.h>
#include <Autonomous.h>

class CrossDefAndShoot: public CommandGroup
{
public:

	CrossDefAndShoot(Autonomous::Defense, Autonomous::Goals, int);  //which type of defense, which goal (high/low),
																	//defense slot we started in front of
	//note: initial defense position is labeled from 1 to 5 from the edge of the field inwards (1 is the low bar)
	/*

	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	*/
};

#endif
