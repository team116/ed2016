/*
 * CrossDefAndShoot.h
 *
 *  Created on: Jan 27, 2016
 *      Author: strahans
 */

#ifndef SRC_COMMANDS_AUTONOMOUS_CROSSDEFANDSHOOT_H_
#define SRC_COMMANDS_AUTONOMOUS_CROSSDEFANDSHOOT_H_

class CrossDefAndShoot {
public:
	CrossDefAndShoot();
	virtual ~CrossDefAndShoot();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_AUTONOMOUS_CROSSDEFANDSHOOT_H_ */
