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
};

#endif /* SRC_COMMANDS_SHOOT_H_ */
