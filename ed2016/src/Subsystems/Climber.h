#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>
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

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

private:
	Climber();
	static Climber* INSTANCE;
	VictorSP* climber_armed_motor;
	ClimberMechanismDirection climber_direction;
};

#endif
