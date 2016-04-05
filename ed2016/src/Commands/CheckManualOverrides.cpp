#include <Commands/CheckManualOverrides.h>
#include <OI.h>
#include <Subsystems/Intake.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/ShooterPitch.h>

const float CheckManualOverrides::MIN_PID_TOGGLE_TIME = 0.5; // how often a pid subsystem and be enabled/disabled

CheckManualOverrides::CheckManualOverrides()
{
	pid_toggle_timer = new Timer();
}

// Called just before this Command runs the first time
void CheckManualOverrides::Initialize()
{
	log->write(Log::TRACE_LEVEL, "CheckManualOverrides initialized");
	pid_toggle_timer->Start();
	pid_toggle_timer->Reset();
}

// Called repeatedly when this Command is scheduled to run
void CheckManualOverrides::Execute()
{
	if (DriverStation::GetInstance().IsEnabled())
	{
		bool enable_sensors;
		if (DriverStation::GetInstance().IsTest() || DriverStation::GetInstance().IsOperatorControl())
		{
			enable_sensors = oi->getSensorEnableSwitch();
		}
		else // DriverStation::GetInstance().IsAutonomous() == true
		{
			enable_sensors = true;
		}


		sensors->enableDriveEncoders(enable_sensors);
		sensors->enableIntakeAngle(enable_sensors);
		sensors->enableLidar(enable_sensors);
		sensors->enableRobotAngle(enable_sensors);
		sensors->enableShooterAngle(enable_sensors);
		sensors->enableShooterHomeSwitch(enable_sensors);
		sensors->enableShooterWheelTachometer(enable_sensors);
		sensors->enableBallSwitch(enable_sensors);

		checkPIDOverrideTimed(enable_sensors && oi->getPIDEnableSwitch());
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CheckManualOverrides::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CheckManualOverrides::End()
{
	log->write(Log::TRACE_LEVEL, "CheckManualOverrides ended");
	pid_toggle_timer->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CheckManualOverrides::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "CheckManualOverrides interrupted");
	End();
}

void CheckManualOverrides::checkPIDOverrideTimed(bool enable)
{
	if (pid_toggle_timer->Get() > MIN_PID_TOGGLE_TIME)
	{
		if (shooter_pitch->isPIDEnabled() != enable)
		{
			if (enable)
			{
				shooter_pitch->Enable();
			}
			else
			{
				shooter_pitch->Disable();
			}
			pid_toggle_timer->Reset();
		}

		if (shooter->isPIDEnabled() != enable)
		{
			if (enable)
			{
				shooter->Enable();
			}
			else
			{
				shooter->Disable();
			}
			pid_toggle_timer->Reset();
		}

		if (intake->isPIDEnabled() != enable)
		{
			if (enable)
			{
				shooter->Enable();
			}
			else
			{
				intake->Disable();
			}
			pid_toggle_timer->Reset();
		}
	}
}
