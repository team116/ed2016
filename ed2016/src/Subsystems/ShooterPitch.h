#ifndef ShooterPitch_H
#define ShooterPitch_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <RobotMap.h>

class ShooterPitch: public PIDSubsystem
{
public:
	enum AnglePresets {
		ONE = 0,
		TWO = 15,
		THREE = 30,
		FOUR = 45,
		FIVE = 60,
		SIX = 75
	};
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

	float getPitchToTarget(PitchType);

	float getP();
	float getI();
	float getD();
	float getF();
	void setP(float);
	void setI(float);
	void setD(float);
	void setF(float);

private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	SpeedController* pitch_angle;

	static const float MANUAL_SPEED;
	static const float TARGET_HEIGHT;
};

#endif
