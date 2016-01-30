/*
 * AngleIntake.h
 *
 *  Created on: Jan 28, 2016
 *      Author: Siddhesh
 */

#ifndef SRC_COMMANDS_ANGLEINTAKE_H_
#define SRC_COMMANDS_ANGLEINTAKE_H_

#include "../CommandBase.h"
#include "WPILib.h"

class AngleIntake: public CommandBase {
public:
	AngleIntake();
	virtual ~AngleIntake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_ANGLEINTAKE_H_ */
