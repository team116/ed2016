#ifndef Winches_H
#define Winches_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <RobotMap.h>

class Winches: public Subsystem
{
public:
	Winches();
	void InitDefaultCommand();

	void setFrontWinchDirection(Utils::VerticalDirection direction);
	void setBackWinchDirection(Utils::VerticalDirection direction);

	void setFrontWinchSpeed(float);
	void setBackWinchSpeed(float);

	Utils::VerticalDirection getFrontWinchDirection();
	Utils::VerticalDirection getBackWinchDirection();

	bool isWinchCurrentSpiking();

private:
	Utils::VerticalDirection front_winch_direction;
	Utils::VerticalDirection back_winch_direction;

	const static float WINCH_SPEED;
	const static float WINCH_CURRENT_SPIKE_THRESHHOLD;

	SpeedController* front_winch;
	SpeedController* back_winch;

};

#endif
