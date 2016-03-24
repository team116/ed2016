#ifndef ShooterPitch_H
#define ShooterPitch_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <RobotMap.h>

class ShooterPitch: public PIDSubsystem
{
public:
	static const int ANGLE_PRESET_COUNT;
	static float getAnglePreset(int index);

	ShooterPitch();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();

	void setAngle(float degrees);
	void setSpeed(float speed);
	void setDirection(Utils::VerticalDirection);
	void checkLimits();

	float getPitchToTarget(float, float);

	bool isPIDEnabled();

	float getP();
	float getI();
	float getD();
	float getF();
	void setP(float);
	void setI(float);
	void setD(float);
	void setF(float);

	static const float SHOOTER_TO_TARGET_HEIGHT;
	static const float LIDAR_TO_SHOOTER_DISTANCE;
	static const float SHOOTER_HEIGHT;

private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	SpeedController* pitch_angle;

	static float* ANGLE_PRESETS;

	static const float MANUAL_SPEED;

	static const float ZERO_ANGLE_ZONE;

	/**
	 * requires_reenable is set to true when
	 * 1) we decide to go to zero degrees,
	 * 2) the home switch is enabled, and
	 * 3) PID is enabled
	 *
	 * When this happens, PID is disabled so that we can just set the speed to -1.0 and wait for the limit
	 * switch to be pressed.  isPIDEnabled() automatically checks for this, and reenables the subsystem
	 * accordingly.
	 */
	bool requires_reenable;

};

#endif
