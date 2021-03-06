/*
 * DoNothing.h
 *
 *  Created on: Jan 27, 2016
 *      Author: strahans
 */

#ifndef SRC_COMMANDS_DONOTHING_H_
#define SRC_COMMANDS_DONOTHING_H_
#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "Autonomous.h"

class DoNothing: public CommandGroup {
public:
	DoNothing();
	virtual ~DoNothing();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};

#endif /* SRC_COMMANDS_DONOTHING_H_ */
