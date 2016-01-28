/*
 * MoveToDefense.h
 *
 *  Created on: Jan 19, 2016
 *      Author: Siddhesh
 */

#ifndef SRC_COMMANDS_MoveToDefense_H_
#define SRC_COMMANDS_MoveToDefense_H_

class MoveToDefense {
public:
	MoveToDefense();
	virtual ~MoveToDefense();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_MoveToDefense_H_ */
