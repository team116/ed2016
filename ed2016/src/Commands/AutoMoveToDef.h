/*
 * AutoMoveToDef.h
 *
 *  Created on: Jan 19, 2016
 *      Author: Siddhesh
 */

#ifndef SRC_COMMANDS_AUTOMOVETODEF_H_
#define SRC_COMMANDS_AUTOMOVETODEF_H_

class AutoMoveToDef {
public:
	AutoMoveToDef();
	virtual ~AutoMoveToDef();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_AUTOMOVETODEF_H_ */
