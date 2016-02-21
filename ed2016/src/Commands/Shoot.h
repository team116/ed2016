#ifndef SRC_COMMANDS_SHOOT_H_
#define SRC_COMMANDS_SHOOT_H_

#include "../CommandBase.h"
#include "WPILib.h"

class Shoot : public CommandBase {
public:
	Shoot();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	Timer* timer;
	static const float SPEED_UP_TIME;
	static const float PUSH_BOULDER; // gives it time to get the boulder in position

	bool interrupted;
};

#endif /* SRC_COMMANDS_SHOOT_H_ */
