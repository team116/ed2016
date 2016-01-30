/*
 * AutoAim.h
 *
 *  Created on: Jan 28, 2016
 *      Author: Siddhesh
 */

#ifndef SRC_COMMANDS_AUTOAIM_H_
#define SRC_COMMANDS_AUTOAIM_H_

#include "../CommandBase.h"
#include "WPILib.h"

class AutoAim: public CommandBase  {
public:
	AutoAim();
	virtual ~AutoAim();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool interrupted;
};

#endif /* SRC_COMMANDS_AUTOAIM_H_ */
