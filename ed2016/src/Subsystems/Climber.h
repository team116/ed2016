#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>
#include <RobotMap.h>
#include <WPILib.h>

class Climber: public Subsystem
{
public:
	Climber();

	void InitDefaultCommand();
	void setClimber(Utils::VerticalDirection direction, float speed = 1.0);
	Utils::VerticalDirection getDirectionClimber();

	void setFrontWinchDirection (Utils::VerticalDirection direction);
	void setBackWinchDirection (Utils::VerticalDirection direction);


	void setFrontWinchSpeed(float);
	void setBackWinchSpeed(float);

	Utils::VerticalDirection getFrontWinchDirection();
	Utils::VerticalDirection getBackWinchDirection();

	bool isWinchCurrentSpiking();

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

private:

	const static float WINCH_SPEED;
	const static float CURRENT_SPIKE_THRESHHOLD;

	Utils::VerticalDirection climber_arm_direction;
	Utils::VerticalDirection front_winch_direction;
	Utils::VerticalDirection back_winch_direction;

	SpeedController* climber_armed_motor;
	SpeedController* front_winch;
	SpeedController* back_winch;

	PowerDistributionPanel* pdp;

};

#endif
