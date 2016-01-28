/*
 * CrossDefense.h
 *
 *  Created on: Jan 27, 2016
 *      Author: strahans
 */

#ifndef SRC_COMMANDS_AUTONOMOUS_CROSSDEFENSE_H_
#define SRC_COMMANDS_AUTONOMOUS_CROSSDEFENSE_H_

class CrossDefense {
public:
	CrossDefense();
	virtual ~CrossDefense();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_AUTONOMOUS_CROSSDEFENSE_H_ */
