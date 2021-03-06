#include "AimShooterToTarget.h"
#include <Subsystems/Shooter.h>
#include <Subsystems/ShooterPitch.h>
#include <Subsystems/Cameras.h>
#include <Subsystems/Sensors.h>
#include <OI.h>

const float ACCEPTED_ERROR = 2.0;
const float AimShooterToTarget::ACCEPTED_LIDAR_ERROR = 5.0;
const float TIMEOUT = 6.0;

AimShooterToTarget::AimShooterToTarget()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(&*shooter);
	Requires(&*shooter_pitch);

	SetTimeout(TIMEOUT);

	pitch = 0.0;
	rpm = 0.0;
	current_pitch = 0.0;
	distance = 0.0;

	interrupted = false;
}

// Called just before this Command runs the first time
void AimShooterToTarget::Initialize()
{
	if(oi->getPIDEnableSwitch()) {
		shooter->Enable();
		shooter_pitch->Enable();
	}
	log->write(Log::TRACE_LEVEL, "AimShooterToTarget initialized");
	interrupted = false;

	if (sensors->lidarDistance() + ShooterPitch::LIDAR_TO_SHOOTER_DISTANCE - cameras->GetDistanceFromTarget() > AimShooterToTarget::ACCEPTED_LIDAR_ERROR)
	{
		distance = cameras->GetDistanceFromTarget() - Cameras::TOWER_TO_GOAL_DISTANCE;
	}
	else
	{
		distance = sensors->lidarDistance() + ShooterPitch::LIDAR_TO_SHOOTER_DISTANCE - Cameras::TOWER_TO_GOAL_DISTANCE;
	}

	rpm = shooter->getRPMPreset(5);
	pitch = shooter_pitch->getPitchToTarget(distance, Shooter::SHOOT_VELOCITY);
	if((pitch < 0) || (pitch > 90)) {
		DriverStation::ReportError("Target out of range. Move closer");
		log->write(Log::WARNING_LEVEL, "Warning: Target out of range");
		interrupted = true;
		return;
	}

	/*DriverStation::ReportError("Calculated Pitch: " + std::to_string(pitch));
	DriverStation::ReportError("RPM: " + std::to_string(rpm));
	DriverStation::ReportError("Lidar: " + std::to_string(sensors->lidarDistance()));
	DriverStation::ReportError("Dis: " + std::to_string(sensors->lidarDistance() + ShooterPitch::LIDAR_TO_SHOOTER_DISTANCE - Cameras::TOWER_TO_GOAL_DISTANCE));*/
	//log->write(Log::DEBUG_LEVEL, "Auto Aim Pitch: %f", pitch);

	shooter_pitch->SetSetpoint(pitch);
	shooter->setRPM(rpm);
}

// Called repeatedly when this Command is scheduled to run
void AimShooterToTarget::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool AimShooterToTarget::IsFinished()
{
	current_pitch = CommandBase::sensors->shooterAngle();
	if(interrupted)
	{
		return true;
	}
	else if(shooter->OnTarget() && (fabs(current_pitch - pitch) <= ACCEPTED_ERROR))
	{
		return true;
	}
	else if(IsTimedOut()) {
		log->write(Log::WARNING_LEVEL, "AimShooterToTarget timed out after %f seconds (current pitch: %f target pitch: %f current rpm: %f target rpm: %f)", TIMEOUT,
				current_pitch, pitch, CommandBase::sensors->speedShooterWheel(), rpm);
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void AimShooterToTarget::End()
{
	log->write(Log::TRACE_LEVEL, "AimShooterToTarget ended (current pitch: %f target pitch: %f current rpm: %f target rpm: %f)", current_pitch, pitch,
			CommandBase::sensors->speedShooterWheel(), rpm);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AimShooterToTarget::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "AimShooterToTarget interrupted (current pitch: %f target pitch: %f current rpm: %f target rpm: %f)", current_pitch, pitch,
			CommandBase::sensors->speedShooterWheel(), rpm);
	End();
}
