#ifndef ShooterPitchPID_H
#define ShooterPitchPID_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
#include <RobotMap.h>

class ShooterPitchPID: public PIDSubsystem
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

	ShooterPitchPID();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();

	void checkLimits();

	//You should call Disable() to manually control the pitch, otherwise the PID will fight against you
	void setDirection(Utils::VerticalDirection);

	float getPitchToTarget(PitchType);

	float getP();
	float getI();
	float getD();
	void setP(float);
	void setI(float);
	void setD(float);

private:
	static const float MANUAL_SPEED;
	static const float TARGET_HEIGHT;

	SpeedController* pitch_angle;
};

#endif
