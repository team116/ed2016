#include <Commands/MaintainShooterAngle.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Subsystems/ShooterPitch.h>
#include <Subsystems/Sensors.h>

const float MaintainShooterAngle::UNKNOWN_ANGLE_POWER = 0.08;
const float MaintainShooterAngle::ANGLE_POWER_SCALE = 0.18;

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
	if (sensors->areShooterAngleEnabled())
	{
		shooter_pitch->setShooterPitchSpeed(ANGLE_POWER_SCALE * cos(M_PI * sensors->shooterAngle() / 180.0));
	}
	else
	{
		shooter_pitch->setShooterPitchSpeed(UNKNOWN_ANGLE_POWER);
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
	shooter_pitch->setShooterPitchDirection(ShooterPitch::ShooterPitchDirection::SHOOTER_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MaintainShooterAngle::Interrupted()
{
	End();
}
