/*
 * AngleIntake.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: Siddhesh
 */

#include <Commands/AngleIntake.h>
#include <Subsystems/Intake.h>
#include <Subsystems/Sensors.h>
#include <cmath>

AngleIntake::AngleIntake(float ang, float error)
{
	Requires(&*intake);
	current_angle = 0.0;
	angle = ang;
	accepted_error = error;
	direction = Intake::INTAKE_STOP;
	interrupted = false;
}

AngleIntake::~AngleIntake()
{
	// TODO Auto-generated destructor stub
}

void AngleIntake::Initialize()
{

}

void AngleIntake::Execute()
{
	current_angle = sensors->intakeAngle();

	if (angle > current_angle)
	{
		direction = Intake::INTAKE_UP;
	}
	else if (angle < current_angle)
	{
		direction = Intake::INTAKE_DOWN;
	}
	else
	{
		direction = Intake::INTAKE_STOP;
	}
	intake->setIntakeAngleDirection(direction);
}

bool AngleIntake::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	else if (abs(angle-current_angle) <= accepted_error)
	{
		return true;
	}
	return false;
}

void AngleIntake::End()
{
	intake->setIntakeAngleDirection(Intake::INTAKE_STOP);
}

void AngleIntake::Interrupted()
{
	End();
	interrupted = true;
}
