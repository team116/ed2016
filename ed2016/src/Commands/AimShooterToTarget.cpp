#include "AimShooterToTarget.h"
#include <Subsystems/Shooter.h>
#include <Subsystems/ShooterPitch.h>
#include <Subsystems/Cameras.h>
#include <Subsystems/Sensors.h>

const float ACCEPTED_ERROR = 2;
const float TIMEOUT = 5;

AimShooterToTarget::AimShooterToTarget()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(&*shooter);
	Requires(&*shooter_pitch);

	SetTimeout(TIMEOUT);

	pitch = 0;
	rpm = 0;
	current_pitch = 0;

	interrupted = false;
}

// Called just before this Command runs the first time
void AimShooterToTarget::Initialize()
{
	log->write(Log::TRACE_LEVEL, "AimShooterToTarget initialized");
	interrupted = false;

	rpm = shooter->getRPMPreset(5);
	//rpm = shooter->getRPMPreset(oi->getShooterSpeedPosition());
	//float vel = M_PI * 0.1016 * (rpm-1000) / 60; // PI * D * RPM / 60
	//float vel = std::stof(SmartDashboard::GetString("DB/String 9", "0"));
	float vel = 10;
	pitch = shooter_pitch->getPitchToTarget(sensors->lidarDistance() + ShooterPitch::LIDAR_TO_SHOOTER_DISTANCE - Cameras::TOWER_TO_GOAL_DISTANCE, vel);
	if((pitch < 0) || (pitch > 90)) {
		DriverStation::ReportError("Target out of range. Move closer");
		log->write(Log::WARNING_LEVEL, "Warning: Target out of range");
		interrupted = true;
		return;
	}

	//DriverStation::ReportError("Calculated Pitch: " + std::to_string(pitch));
	//DriverStation::ReportError("RPM: " + std::to_string(rpm));
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
