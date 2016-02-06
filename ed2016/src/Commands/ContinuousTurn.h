#ifndef ContinuousTurn_H
#define ContinuousTurn_H

#include <CommandBase.h>
#include <WPILib.h>

class ContinuousTurn: public CommandBase
{
public:
	enum Direction {
		RIGHT,
		LEFT,
		STOP
	};
	ContinuousTurn(Direction);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	Direction direction;
	static const float TURN_SPEED;
	bool interrupted;
};

#endif
