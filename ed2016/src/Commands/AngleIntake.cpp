/*
 * AngleIntake.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: Siddhesh
 */

#include <Commands/AngleIntake.h>
#include <Subsystems/Intake.h>

AngleIntake::AngleIntake()
{
	Requires(intake);

}

AngleIntake::~AngleIntake()
{
	// TODO Auto-generated destructor stub
}

void Initialize()
{

}

void Execute()
{

}

bool IsFinished()
{
	return false;
}

void End()
{

}

void Interrupted()
{

}
