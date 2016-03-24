#include "AutoWinch.h"
#include <Subsystems/Winches.h>
#include <Subsystems/Sensors.h>
#include <OI.h>

const float AutoWinch::DEGREE_TOLERANCE = 10.0;
const float AutoWinch::OFFSET_SPEED = 0.2;

AutoWinch::AutoWinch()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(&*winches);

	pid_enabled = false;
	target_angle = 0;
}

// Called just before this Command runs the first time
void AutoWinch::Initialize()
{
	pid_enabled = oi->getPIDEnableSwitch();
	log->write(Log::TRACE_LEVEL, "AutoWinch Initialized. PID mode: %d", pid_enabled);
	target_angle = sensors->robotPitch();
	if(pid_enabled) {
		winches->SetAbsoluteTolerance(DEGREE_TOLERANCE);
		winches->SetSetpoint(target_angle);
		winches->Enable();
	}
}

// Called repeatedly when this Command is scheduled to run
void AutoWinch::Execute()
{
	if(oi->getPIDEnableSwitch() != pid_enabled) {
		pid_enabled = oi->getPIDEnableSwitch();

		log->write(Log::INFO_LEVEL, "PID switch was toggled during auto winch. PID: %d" + pid_enabled);

		if(pid_enabled) {
			winches->SetAbsoluteTolerance(DEGREE_TOLERANCE);
			winches->SetSetpoint(target_angle);
			winches->Enable();
		}
		else {
			winches->Disable();
		}
	}

	if(!pid_enabled) {
		float current_angle = sensors->robotPitch();
		float degrees_off = current_angle - target_angle;

		if(degrees_off < -DEGREE_TOLERANCE) {
			log->write(Log::INFO_LEVEL, "Front too high, slowing down. Current Angle: %f Target: %f Off: %f", current_angle, target_angle, degrees_off);
			winches->setBackWinchSpeed(-Winches::PID_BASE_SPEED);
			winches->setFrontWinchSpeed(-Winches::PID_BASE_SPEED + OFFSET_SPEED);
		}
		else if(degrees_off > DEGREE_TOLERANCE) {
			log->write(Log::INFO_LEVEL, "Front too low, speeding up. Current Angle: %f Target: %f Off: %f", current_angle, target_angle, degrees_off);
			winches->setBackWinchSpeed(-Winches::PID_BASE_SPEED);
			winches->setFrontWinchSpeed(-Winches::PID_BASE_SPEED - OFFSET_SPEED);
		}
		else {
			log->write(Log::INFO_LEVEL, "Front level. Current Angle: %f Target: %f Off: %f", current_angle, target_angle, degrees_off);
			winches->setBackWinchSpeed(-Winches::PID_BASE_SPEED);
			winches->setFrontWinchSpeed(-Winches::PID_BASE_SPEED);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutoWinch::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void AutoWinch::End()
{
	log->write(Log::TRACE_LEVEL, "AutoWinch Ended");
	winches->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoWinch::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "AutoWinch Interrupted");
	End();
}
