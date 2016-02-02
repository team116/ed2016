/*
 * AutoAim.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: Siddhesh
 */

#include <Commands/AutoAim.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/Sensors.h>

AutoAim::AutoAim() {
	Requires(shooter);

	interrupted = false;
}

AutoAim::~AutoAim() {
	// TODO Auto-generated destructor stub
}

void AutoAim::Initialize()
{

}

void AutoAim::Execute()
{

}

bool AutoAim::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	return false;
}

void AutoAim::End()
{

}

void AutoAim::Interrupted()
{
	End();
	interrupted = true;
}
