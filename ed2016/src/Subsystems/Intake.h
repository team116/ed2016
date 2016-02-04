#ifndef Yellow_H
#define Yellow_H

#include <Commands/Subsystem.h>
#include <RobotMap.h>
#include <WPILib.h>

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

	enum IntakeAngleDirection
	{
		INTAKE_UP,
		INTAKE_STOP,
		INTAKE_DOWN
	};
	void setIntakeDirection(IntakeDirection);
	void setIntakeAngleDirection(IntakeAngleDirection);

private:
	Intake();
	static Intake* INSTANCE;

	MOTOR_TYPE* intake_roller;
	MOTOR_TYPE* intake_angle;

};

#endif
