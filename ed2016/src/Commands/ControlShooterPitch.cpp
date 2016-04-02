#include <Commands/ControlShooterPitch.h>
#include <Log.h>
#include <OI.h>

ControlShooterPitch::ControlShooterPitch()
{
	last_fuego_value = false;
	last_auto_aim_value = false;

	shoot = new Shoot();
	auto_shoot = new AutoShoot();

	move_shooter_up = new MoveShooter(Utils::VerticalDirection::UP);
	stop_shooter = new MoveShooter(Utils::VerticalDirection::V_STILL);
	move_shooter_down = new MoveShooter(Utils::VerticalDirection::DOWN);
}

// Called just before this Command runs the first time
void ControlShooterPitch::Initialize()
{
	log->write(Log::TRACE_LEVEL, "ControlShooterPitch initialized");
}

// Called repeatedly when this Command is scheduled to run
void ControlShooterPitch::Execute()
{
	bool fuego_value = oi->getFuegoButton();
	bool auto_aim_value = oi->getAutoAimButton();

	if (last_fuego_value != fuego_value)
	{
		if (oi->getSensorOverrideSwitch())
		{
			if (fuego_value)
			{
				Scheduler::GetInstance()->AddCommand(move_shooter_up);
			}
			else
			{
				Scheduler::GetInstance()->AddCommand(stop_shooter);
			}
		}
		else
		{
			Scheduler::GetInstance()->AddCommand(shoot);
		}
	}

	if (last_auto_aim_value != auto_aim_value)
	{
		if (oi->getSensorOverrideSwitch())
		{
			if (auto_aim_value)
			{
				Scheduler::GetInstance()->AddCommand(move_shooter_down);
			}
			else
			{
				Scheduler::GetInstance()->AddCommand(stop_shooter);
			}
		}
		else
		{
			Scheduler::GetInstance()->AddCommand(auto_shoot);
		}
	}

	last_fuego_value = fuego_value;
	last_auto_aim_value = auto_aim_value;
}

// Make this return true when this Command no longer needs to run execute()
bool ControlShooterPitch::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ControlShooterPitch::End()
{
	log->write(Log::TRACE_LEVEL, "ControlShooterPitch ended");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ControlShooterPitch::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "ControlShooterPitch interrupted");
	End();
}
