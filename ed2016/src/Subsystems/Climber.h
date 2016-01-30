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
	enum ClimberMechanismSide
	{
		CLIMBER_BACK,
		CLIMBER_FRONT
	};
	void InitDefaultCommand();
	static Climber* getInstance();
	void setFrontClimber(ClimberMechanismDirection direction);
	void setBackClimber(ClimberMechanismDirection direction);
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

private:
	Climber();
	static Climber* INSTANCE;
	CANTalon* front_winch;
	CANTalon* back_winch;

};

#endif
