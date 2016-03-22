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
	float pitch;
	float rpm;
	float azimuth;

	float current_pitch;

	static const float P;
	static const float MIN_TURN_SPEED;
	static const float MAX_TURN_SPEED;
	static const float ACCEPTED_ERROR;
	static const float TIMEOUT;
};

#endif /* SRC_COMMANDS_AUTOAIM_H_ */
