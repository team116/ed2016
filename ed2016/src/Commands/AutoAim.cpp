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

const float AutoAim::TURN_SPEED = 0.5;
const float AutoAim::ACCEPTED_ERROR = 2;
const float AutoAim::TIMEOUT = 10;

AutoAim::AutoAim() {
	Requires(&*shooter);
	Requires(&*shooter_pitch);
	Requires(&*mobility);

	pitch = 0;
	rpm = 0;
	current_pitch = 0;
	azimuth = 0;
	interrupted = false;

	SetTimeout(TIMEOUT);
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
	rpm = shooter->getRPMPreset(5);
	//rpm = shooter->getSpeedToTarget(90 - pitch);
	float vel = M_PI * 0.1016 * rpm; // PI * D * RPM
	pitch = shooter_pitch->getPitchToTarget(ShooterPitch::PitchType::LIDAR, 14.35);

	DriverStation::ReportError("Calculated Pitch: " + std::to_string(pitch));
	DriverStation::ReportError("Calculated RPM: " + std::to_string(rpm));

	if((rpm > shooter->getRPMPreset(5)) || (rpm < shooter->getRPMPreset(0)) || (pitch < 0) || (pitch > 90)) {
		log->write(Log::INFO_LEVEL, "Target is out of range(Angle: %f Calculated RPM: %f)", pitch, rpm);
	}
	else {
		shooter_pitch->SetSetpoint(pitch);
		shooter->Enable();
		shooter->SetSetpoint(rpm);

		/*for(int x = 0; x < 6; x++) {
			if(rpm < (shooter->getRPMPreset(x) + 225)) {
				DriverStation::ReportError("Setting RPM to " + std::to_string(shooter->getRPMPreset(x)));
				shooter->setShooterSpeed(shooter->getSpeedPreset(x));
				break;
			}
		}*/
	}
	if (cameras->canSeeGoal())
	{
		azimuth = cameras->AzimuthDegreesFromTarget();

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
	shooter_pitch->setDirection(Utils::VerticalDirection::V_STILL);
}

void AutoAim::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "Auto Aim Interrupted");
	End();
	interrupted = true;
}
