#ifndef Yellow_H
#define Yellow_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Intake: public Subsystem
{
public:
	static Intake* getInstance();
	void InitDefaultCommand();
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	enum IntakeDirection
	{
		INTAKE_IN,
		INTAKE_STILL,
		INTAKE_OUT
	};
	void setIntakeDirection(IntakeDirection value);

private:
	Intake();
	static Intake* INSTANCE;

	CANTalon* intake_roller;

};

#endif
