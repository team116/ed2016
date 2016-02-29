/*
 * AngleIntake.h
 *
 *  Created on: Jan 28, 2016
 *      Author: Siddhesh
 */

#ifndef SRC_COMMANDS_ANGLEINTAKE_H_
#define SRC_COMMANDS_ANGLEINTAKE_H_

#include <CommandBase.h>
#include <Subsystems/Intake.h>
#include <WPILib.h>

class AngleIntake: public CommandBase {
public:
	AngleIntake(float ang, float error = 5.0);
	virtual ~AngleIntake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	static const float TIMEOUT;

	Utils::VerticalDirection direction;
	float current_angle;
	float angle;
	float accepted_error;
	bool interrupted;

	static float last_angle;
};

#endif /* SRC_COMMANDS_ANGLEINTAKE_H_ */
