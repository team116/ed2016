#include <Commands/MaintainShooterAngle.h>
#include <Commands/SetShooterPitch.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Subsystems/ShooterPitch.h>
#include <Subsystems/Sensors.h>

const float MaintainShooterAngle::UNKNOWN_ANGLE_POWER = 0.08;
const float MaintainShooterAngle::ANGLE_POWER_SCALE1 = 0.145;
const float MaintainShooterAngle::ANGLE_POWER_SCALE2 = 0.155;
const float MaintainShooterAngle::POWER_SCALE_FENCE = 10.0;

MaintainShooterAngle::MaintainShooterAngle()
{
	Requires(&*shooter_pitch);
}

// Called just before this Command runs the first time
void MaintainShooterAngle::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void MaintainShooterAngle::Execute()
{
	if (sensors->isShooterHomeSwitchHorizontal())
	{
		shooter_pitch->setSpeed(0.0);
	}
	if (sensors->areShooterAngleEnabled())
	{
		float pitch = sensors->shooterAngle();
		float scale;
		if (pitch < POWER_SCALE_FENCE)
		{
			scale = ANGLE_POWER_SCALE1;
		}
		else
		{
			scale = ANGLE_POWER_SCALE2;
		}
		shooter_pitch->setSpeed(scale * (1.0 - sin(M_PI * pitch / 180.0)));
	}
	else
	{
		shooter_pitch->setSpeed(UNKNOWN_ANGLE_POWER);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool MaintainShooterAngle::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MaintainShooterAngle::End()
{
	shooter_pitch->setDirection(Utils::VerticalDirection::V_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MaintainShooterAngle::Interrupted()
{
	End();
}
