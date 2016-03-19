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
#include <OI.h>

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
	current_pitch = CommandBase::sensors->shooterAngle();

	rpm = shooter->getRPMPreset(CommandBase::oi->getShooterSpeedPosition());
	//rpm = shooter->getSpeedToTarget(90 - pitch);
	float vel = M_PI * 0.1016 * rpm / 60; // PI * D * RPM / 60
	pitch = shooter_pitch->getPitchToTarget(ShooterPitch::PitchType::LIDAR, std::stof(SmartDashboard::GetString("DB/String 8", "0")));
	if(pitch == -1) {
		DriverStation::ReportError("Target out of range. Raise the speed and/or move closer");
		log->write(Log::WARNING_LEVEL, "Warning: Target out of range");
		interrupted = true;
		return;
	}

	DriverStation::ReportError("Calculated Pitch: " + std::to_string(pitch));
	DriverStation::ReportError("RPM: " + std::to_string(rpm));

	if((rpm > shooter->getRPMPreset(5)) || (rpm < shooter->getRPMPreset(0)) || (pitch < 0) || (pitch > 90)) {
		log->write(Log::INFO_LEVEL, "Target is out of range(Angle: %f Calculated RPM: %f)", pitch, rpm);
	}
	else {
		shooter_pitch->SetSetpoint(pitch);
		shooter->Enable();
		shooter->setRPM(rpm);
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
			if(shooter->OnTarget()) {
				return true;
			}
		}
	}
	else if(IsTimedOut())
	{
		log->write(Log::WARNING_LEVEL, "Warning: AutoAim timed out after %f seconds (Pitch: %f Azimuth Deg Off: %f Shooter On Target: %d)", current_pitch, azimuth, shooter->OnTarget());
		return true;
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
