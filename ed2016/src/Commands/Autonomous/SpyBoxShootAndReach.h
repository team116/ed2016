/*
 * SpyBoxShootAndReach.h
 *
 *  Created on: Jan 27, 2016
 *      Author: strahans
 */

#ifndef SRC_COMMANDS_AUTONOMOUS_SPYBOXSHOOTANDREACH_H_
#define SRC_COMMANDS_AUTONOMOUS_SPYBOXSHOOTANDREACH_H_

class SpyBoxShootAndReach {
public:
	SpyBoxShootAndReach();
	virtual ~SpyBoxShootAndReach();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_AUTONOMOUS_SPYBOXSHOOTANDREACH_H_ */
