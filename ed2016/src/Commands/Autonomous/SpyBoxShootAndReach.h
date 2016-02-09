/*
 * SpyBoxShootAndReach.h
 *
 *  Created on: Jan 27, 2016
 *      Author: strahans
 */

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include <Autonomous.h>
#ifndef SRC_COMMANDS_AUTONOMOUS_SPYBOXSHOOTANDREACH_H_
#define SRC_COMMANDS_AUTONOMOUS_SPYBOXSHOOTANDREACH_H_

class SpyBoxShootAndReach: public CommandGroup {
public:
	SpyBoxShootAndReach(Autonomous::Goals);
	virtual ~SpyBoxShootAndReach();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_AUTONOMOUS_SPYBOXSHOOTANDREACH_H_ */
