/*
 * OperateClimber.h
 *
 *  Created on: Jan 28, 2016
 *      Author: Siddhesh
 */

#ifndef SRC_COMMANDS_OPERATECLIMBER_H_
#define SRC_COMMANDS_OPERATECLIMBER_H_

#include "../CommandBase.h"
#include "WPILib.h"
#include <Subsystems/Climber.h>

class OperateClimber: public CommandBase {
public:
	OperateClimber(Climber::ClimberMechanismDirection);
	virtual ~OperateClimber();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	Climber::ClimberMechanismDirection direction;
	bool interrupted;
};

#endif /* SRC_COMMANDS_OPERATECLIMBER_H_ */
