#include <CheckManualOverrides.h>
#include <CommandBase.h>
#include <OI.h>
#include <Subsystems/Intake.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/ShooterPitch.h>
#include <vector>

using namespace std;

namespace CheckManualOverrides
{
	const float MIN_PID_TOGGLE_TIME = 0.5; // how often a pid subsystem can be enabled/disabled
	Timer* pid_toggle_timer;

	struct Request
	{
		PIDSubsystem* subsystem;
		bool enable;
	};
	vector<Request>* requests;

	void checkPIDOverrideTimed(bool enable);

	void initialize()
	{
		pid_toggle_timer = new Timer();
		pid_toggle_timer->Start();
		pid_toggle_timer->Reset();

		requests = new vector<Request>();
	}

	void process()
	{
		if (DriverStation::GetInstance().IsEnabled())
		{
			bool enable_sensors;
			if (DriverStation::GetInstance().IsTest() || DriverStation::GetInstance().IsOperatorControl())
			{
				enable_sensors = CommandBase::oi->getSensorEnableSwitch();
			}
			else // DriverStation::GetInstance().IsAutonomous() == true
			{
				enable_sensors = true;
			}


			CommandBase::sensors->enableDriveEncoders(enable_sensors);
			CommandBase::sensors->enableIntakeAngle(enable_sensors);
			CommandBase::sensors->enableLidar(enable_sensors);
			CommandBase::sensors->enableRobotAngle(enable_sensors);
			CommandBase::sensors->enableShooterAngle(enable_sensors);
			CommandBase::sensors->enableShooterHomeSwitch(enable_sensors);
			CommandBase::sensors->enableShooterWheelTachometer(enable_sensors);
			CommandBase::sensors->enableBallSwitch(enable_sensors);

			checkPIDOverrideTimed(enable_sensors && CommandBase::oi->getPIDEnableSwitch());
		}
	}

	void checkPIDOverrideTimed(bool enable)
	{
		if (pid_toggle_timer->Get() > MIN_PID_TOGGLE_TIME)
		{
			if (CommandBase::shooter_pitch->isPIDEnabled() != enable)
			{
				if (enable)
				{
					CommandBase::shooter_pitch->Enable();
				}
				else
				{
					CommandBase::shooter_pitch->Disable();
				}
				pid_toggle_timer->Reset();
			}

			if (CommandBase::shooter->isPIDEnabled() != enable)
			{
				if (enable)
				{
					CommandBase::shooter->Enable();
				}
				else
				{
					CommandBase::shooter->Disable();
				}
				pid_toggle_timer->Reset();
			}

			if (CommandBase::intake->isPIDEnabled() != enable)
			{
				if (enable)
				{
					CommandBase::shooter->Enable();
				}
				else
				{
					CommandBase::intake->Disable();
				}
				pid_toggle_timer->Reset();
			}

			for (vector<Request>::iterator it = requests->begin(); it != requests->end(); ++it)
			{
				if (it->enable)
				{
					it->subsystem->Enable();
				}
				else
				{
					it->subsystem->Disable();
				}
			}
			requests->clear();
		}
	}

	void requestPIDEnable(PIDSubsystem* subsystem, bool enable)
	{
		Request request;
		request.subsystem = subsystem;
		request.enable = enable;

		bool found_duplicate = false;
		for (vector<Request>::iterator it = requests->begin(); it != requests->end(); ++it)
		{
			if (it->subsystem == subsystem)
			{
				it->enable = enable;
				found_duplicate = true;
				break;
			}
		}

		if (!found_duplicate)
		{
			requests->push_back(request);
		}
	}
}
