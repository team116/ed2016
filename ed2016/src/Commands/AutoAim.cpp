/*
 * AutoAim.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: Siddhesh
 */

#include <Commands/AutoAim.h>
#include <Subsystems/ShooterPitch.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Cameras.h>
#include <Subsystems/Mobility.h>

const float AutoAim::TURN_SPEED = 0.75;
const float AutoAim::ACCEPTED_ERROR = 2;

AutoAim::AutoAim() {
	Requires(&*shooter);
	Requires(&*shooter_pitch);
	Requires(&*mobility);

	pitch = 0;
	current_pitch = 0;
	azimuth = 0;
	interrupted = false;
}

AutoAim::~AutoAim() {
	// TODO Auto-generated destructor stub
}

void AutoAim::Initialize()
{
	interrupted = false;
}

void AutoAim::Execute()
{
	if (cameras->canSeeGoal())
	{
		current_pitch = sensors->shooterAngle();
		pitch = cameras->PitchFromHorizontal();
		azimuth = cameras->AzimuthDegreesFromTarget();


		if (pitch < current_pitch)
		{
			shooter_pitch->setShooterPitchDirection(ShooterPitch::SHOOTER_DOWN);
		}
		else if (pitch > current_pitch)
		{
			shooter_pitch->setShooterPitchDirection(ShooterPitch::SHOOTER_UP);
		}
		else
		{
			shooter_pitch->setShooterPitchDirection(ShooterPitch::SHOOTER_STILL);
		}



		if (azimuth < 0.0)
		{
			mobility->setLeft(-TURN_SPEED);
			mobility->setRight(TURN_SPEED);
		}
		else
		{
			mobility->setLeft(TURN_SPEED);
			mobility->setRight(-TURN_SPEED);
		}

	}
}

bool AutoAim::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	else if (azimuth > -ACCEPTED_ERROR && azimuth < ACCEPTED_ERROR)
	{
		if(current_pitch > pitch - ACCEPTED_ERROR && current_pitch < pitch + ACCEPTED_ERROR)
		{
			return true;
		}
	}
	return false;
}

void AutoAim::End()
{
	mobility->setStraight(0.0);
	shooter_pitch->setShooterPitchDirection(ShooterPitch::SHOOTER_STILL);
}

void AutoAim::Interrupted()
{
	End();
	interrupted = true;
}
