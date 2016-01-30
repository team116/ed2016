/*
 * RunIntake.h
 *
 *  Created on: Jan 28, 2016
 *      Author: Siddhesh
 */

#ifndef SRC_COMMANDS_RUNINTAKE_H_
#define SRC_COMMANDS_RUNINTAKE_H_

#include "../CommandBase.h"
#include "WPILib.h"
#include <Subsystems/Intake.h>

class RunIntake: public CommandBase  {
public:
	RunIntake(Intake::IntakeDirection dir);
	virtual ~RunIntake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	Intake::IntakeDirection direction;

	bool interrupted;
};

#endif /* SRC_COMMANDS_RUNINTAKE_H_ */
