/*
 * AutoAim.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: Siddhesh
 */

#include <Commands/AutoAim.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/ShooterPitch.h>
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
	log->write(Log::TRACE_LEVEL, "Auto Aim Initialized");
	interrupted = false;
}

void AutoAim::Execute()
{
	if (cameras->canSeeGoal())
	{
		current_pitch = sensors->shooterAngle();
		pitch = shooter_pitch->getPitchToTarget(ShooterPitch::PitchType::LIDAR);
		azimuth = cameras->AzimuthDegreesFromTarget();

		if (pitch + ACCEPTED_ERROR < current_pitch)
		{
			shooter_pitch->setShooterPitchDirection(Utils::VerticalDirection::DOWN);
		}
		else if (pitch - ACCEPTED_ERROR > current_pitch)
		{
			shooter_pitch->setShooterPitchDirection(Utils::VerticalDirection::UP);
		}
		else
		{
			shooter_pitch->setShooterPitchDirection(Utils::VerticalDirection::V_STILL);
		}



		if (azimuth < -ACCEPTED_ERROR)
		{
			mobility->setLeft(-TURN_SPEED);
			mobility->setRight(TURN_SPEED);
		}
		else if (azimuth > ACCEPTED_ERROR)
		{
			mobility->setLeft(TURN_SPEED);
			mobility->setRight(-TURN_SPEED);
		}
		else
		{
			mobility->setLeft(0.0);
			mobility->setRight(0.0);
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
	log->write(Log::TRACE_LEVEL, "Auto Aim Ended");
	mobility->setStraight(0.0);
	shooter_pitch->setShooterPitchDirection(Utils::VerticalDirection::V_STILL);
}

void AutoAim::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "Auto Aim Interrupted");
	End();
	interrupted = true;
}
