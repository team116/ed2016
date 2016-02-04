#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>
#include <RobotMap.h>
#include <WPILib.h>

class Climber: public Subsystem
{
public:
	enum ClimberMechanismDirection
		{
			CLIMBER_ARM_UP,
			CLIMBER_ARM_DOWN,
			CLIMBER_ARM_STILL
		};

	void InitDefaultCommand();
	static Climber* getInstance();
	void setClimber(ClimberMechanismDirection direction);
	ClimberMechanismDirection getDirectionClimber();

	enum WinchPullDirection
	{
			ROBOT_PULL_UP,
			ROBOT_PULL_DOWN,
			ROBOT_STILL
	};
	void setFrontWinch (WinchPullDirection direction);
	void setBackWinch (WinchPullDirection direction);

	WinchPullDirection getFrontWinchDirection();
	WinchPullDirection getBackWinchDirection();

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

private:
	Climber();
	static Climber* INSTANCE;

	const static float WINCH_SPEED;

	ClimberMechanismDirection climber_arm_direction;
	WinchPullDirection front_winch_direction;
	WinchPullDirection back_winch_direction;

	MOTOR_TYPE* climber_armed_motor;
	MOTOR_TYPE* front_winch;
	MOTOR_TYPE* back_winch;


};

#endif
