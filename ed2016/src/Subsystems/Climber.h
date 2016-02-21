#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>
#include <RobotMap.h>
#include <WPILib.h>

class Climber: public Subsystem
{
public:
	Climber();

	enum ClimberArmDirection
		{
			CLIMBER_ARM_UP,
			CLIMBER_ARM_DOWN,
			CLIMBER_ARM_STILL
		};

	void InitDefaultCommand();
	void setClimber(ClimberArmDirection direction, float speed = 1.0);
	ClimberArmDirection getDirectionClimber();

	enum WinchDirection
	{
			ROBOT_PULL_UP,
			ROBOT_PULL_DOWN,
			ROBOT_STILL
	};
	void setFrontWinch (WinchDirection direction);
	void setBackWinch (WinchDirection direction);

	WinchDirection getFrontWinchDirection();
	WinchDirection getBackWinchDirection();

	bool isWinchCurrentSpiking();

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

private:

	const static float WINCH_SPEED;
	const static float CURRENT_SPIKE_THRESHHOLD;

	ClimberArmDirection climber_arm_direction;
	WinchDirection front_winch_direction;
	WinchDirection back_winch_direction;

	SpeedController* climber_armed_motor;
	SpeedController* front_winch;
	SpeedController* back_winch;

	PowerDistributionPanel* pdp;

};

#endif
