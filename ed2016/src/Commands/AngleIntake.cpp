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
	direction = Utils::VerticalDirection::V_STILL;
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
		direction = Utils::VerticalDirection::UP;
	}
	else if (angle < current_angle)
	{
		direction = Utils::VerticalDirection::DOWN;
	}
	else
	{
		direction = Utils::VerticalDirection::V_STILL;
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
	intake->setIntakeAngleDirection(Utils::VerticalDirection::V_STILL);
}

void AngleIntake::Interrupted()
{
	End();
	interrupted = true;
}
