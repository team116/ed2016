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
	AngleIntake(float, float);
	virtual ~AngleIntake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	Intake::IntakeAngleDirection direction;
	float current_angle;
	float angle;
	float accepted_error;

	bool interrupted;
};

#endif /* SRC_COMMANDS_ANGLEINTAKE_H_ */
