/*
 * JoystickXTurn.h
 *
 *  Created on: Mar 15, 2016
 *      Author: amanzeb
 */

#ifndef SRC_COMMANDS_JOYSTICKTURN_H_
#define SRC_COMMANDS_JOYSTICKTURN_H_

#include <CommandBase.h>
#include "WPILib.h"
#include "OI.h"

class JoystickTurn : public CommandBase
{
public:
	enum JoystickDirectZ
	{
		RIGHT = 2,
		LEFT = 1
	};

	JoystickTurn(JoystickDirectZ);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	JoystickDirectZ joystick_used;

	float curr_left_speed;
	float curr_right_speed;
	float joystick_value;
	float speed_multiplyer;
};

#endif /* SRC_COMMANDS_JOYSTICKTURN_H_ */
