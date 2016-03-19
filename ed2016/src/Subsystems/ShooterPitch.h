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

	enum PitchType {
		CAMERA,
		LIDAR
	};

	ShooterPitch();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();

	void setSpeed(float speed);
	void setDirection(Utils::VerticalDirection);
	void checkLimits();

	float getPitchToTarget(PitchType, float);

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

	static float DISTANCE;

private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	SpeedController* pitch_angle;

	static float* ANGLE_PRESETS;

	static const float MANUAL_SPEED;
	static const float LIDAR_TO_SHOOTER_DISTANCE;
	static const float SHOOTER_HEIGHT;
	static const float TARGET_HEIGHT;
};

#endif
