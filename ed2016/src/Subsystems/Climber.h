#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>
#include <RobotMap.h>
#include <WPILib.h>

class Climber: public Subsystem
{
public:
	enum ClimberArmDirection
		{
			CLIMBER_ARM_UP,
			CLIMBER_ARM_DOWN,
			CLIMBER_ARM_STILL
		};

	void InitDefaultCommand();
	static Climber* getInstance();
	void setClimber(ClimberArmDirection direction, float speed = 0.0);
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

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

private:
	Climber();
	static Climber* INSTANCE;

	const static float WINCH_SPEED;

	ClimberArmDirection climber_arm_direction;
	WinchDirection front_winch_direction;
	WinchDirection back_winch_direction;

	MOTOR_TYPE* climber_armed_motor;
	MOTOR_TYPE* front_winch;
	MOTOR_TYPE* back_winch;


};

#endif
