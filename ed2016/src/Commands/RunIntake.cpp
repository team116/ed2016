/*
 * RunIntake.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: Siddhesh
 */

#include <Commands/RunIntake.h>
#include <Subsystems/Intake.h>

RunIntake::RunIntake(Intake::IntakeDirection dir)
{
	Requires(intake);
	direction = dir;
	interrupted = false;
}

RunIntake::~RunIntake()
{
	// TODO Auto-generated destructor stub
}

void RunIntake::Initialize()
{

}

void RunIntake::Execute()
{
	intake->setIntakeDirection(direction);
}

bool RunIntake::IsFinished()
{
	/* I'm assuming that RunIntake is scheduled when a driver hits a button on the joystick and then is interrupted
	 * when the driver releases the button.*/
	if(interrupted)
	{
		return true;
	}
	return false;
}

void RunIntake::End()
{
	intake->setIntakeDirection(Intake::INTAKE_STILL);
}

void RunIntake::Interrupted()
{
	End();
	interrupted = true;
}
