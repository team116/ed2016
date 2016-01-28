/*
 * SpyBoxShoot.h
 *
 *  Created on: Jan 27, 2016
 *      Author: strahans
 */

#ifndef SRC_COMMANDS_AUTONOMOUS_SPYBOXSHOOT_H_
#define SRC_COMMANDS_AUTONOMOUS_SPYBOXSHOOT_H_

class SpyBoxShoot {
public:
	SpyBoxShoot();
	virtual ~SpyBoxShoot();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_AUTONOMOUS_SPYBOXSHOOT_H_ */
