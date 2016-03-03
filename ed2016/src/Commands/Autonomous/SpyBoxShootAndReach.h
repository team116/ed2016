/*
 * SpyBoxShootAndReach.h
 *
 *  Created on: Jan 27, 2016
 *      Author: strahans
 */

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include <Autonomous.h>
#include <Log.h>
#ifndef SRC_COMMANDS_AUTONOMOUS_SPYBOXSHOOTANDREACH_H_
#define SRC_COMMANDS_AUTONOMOUS_SPYBOXSHOOTANDREACH_H_

class SpyBoxShootAndReach: public CommandGroup {
public:
	SpyBoxShootAndReach(Autonomous::Goals);
private:
	Log* log;
};

#endif /* SRC_COMMANDS_AUTONOMOUS_SPYBOXSHOOTANDREACH_H_ */
