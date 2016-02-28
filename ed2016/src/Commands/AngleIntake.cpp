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

const float AngleIntake::TIMEOUT = 0.05;

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
	log->write(Log::TRACE_LEVEL, "Angle Intake Initialized (angle, %f)", angle);
	SetTimeout(TIMEOUT * fabs(angle - sensors->intakeAngle()));
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
	else if(IsTimedOut()) {
		Log::getInstance()->write(Log::WARNING_LEVEL, "AngleIntake timed out when trying to reach angle %f (Current Angle: %f)", angle, current_angle);
		return true;
	}
	return false;
}

void AngleIntake::End()
{
	log->write(Log::TRACE_LEVEL, "AngleIntake Ended");
	intake->setIntakeAngleDirection(Utils::VerticalDirection::V_STILL);
}

void AngleIntake::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "AngleIntake Interrupted");
	End();
	interrupted = true;
}
