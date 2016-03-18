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

	const static float DEPLOY_ARM_SPEED;
	const static float RETRACT_ARM_SPEED;
	void setClimber(Utils::VerticalDirection direction, float speed = RETRACT_ARM_SPEED);

	Utils::VerticalDirection getDirectionClimber();
	bool isClimberCurrentSpiking();

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

private:
	const static float CLIMBER_CURRENT_SPIKE_THRESHHOLD;

	Utils::VerticalDirection climber_arm_direction;

	SpeedController* climber_armed_motor;

};

#endif
