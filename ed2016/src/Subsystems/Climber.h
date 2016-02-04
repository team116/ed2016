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
			CLIMBER_UP,
			CLIMBER_DOWN,
			CLIMBER_STILL
		};

	void InitDefaultCommand();
	static Climber* getInstance();
	void setClimber(ClimberMechanismDirection direction);
	ClimberMechanismDirection getDirectionClimber();

	enum FrontWinchPullDirection
	{
			ROBOT_PULL_UP,
			ROBOT_PULL_DOWN,
			ROBOT_STILL
	};
	void setFrontWinch (FrontWinchPullDirection direction);

	enum BackWinchPullDirection
	{
			PULL_UP_ROBOT,
			PULL_DOWN_ROBOT,
			STILL_ROBOT
	};
	void setBackWinch (BackWinchPullDirection direction);

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

private:
	Climber();
	static Climber* INSTANCE;

	const static float WINCH_SPEED;

	ClimberMechanismDirection climber_direction;
	FrontWinchPullDirection front_winch_direction;
	BackWinchPullDirection back_winch_direction;

	MOTOR_TYPE* climber_armed_motor;
	MOTOR_TYPE* front_winch;
	MOTOR_TYPE* back_winch;


};

#endif
