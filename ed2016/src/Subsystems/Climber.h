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
	void setFrontWinchDirection (WinchDirection direction);
	void setBackWinchDirection (WinchDirection direction);

	void setFrontWinchSpeed(float);
	void setBackWinchSpeed(float);

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

	MOTOR_TYPE* climber_armed_motor;
	MOTOR_TYPE* front_winch;
	MOTOR_TYPE* back_winch;

	PowerDistributionPanel* pdp;

};

#endif
