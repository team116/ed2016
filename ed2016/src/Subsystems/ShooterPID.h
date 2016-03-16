#ifndef ShooterPID_H
#define ShooterPID_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"

class ShooterPID: public PIDSubsystem
{
public:
	ShooterPID();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();

	void setShooterSpeed(float speed);

	float getRPMPreset(int preset); // 0 to 5
	float getSpeedPreset(int preset); // 0 to 5

	float getSpeedToTarget(float angle);

	float getP();
	float getI();
	float getD();
	float getF();
	void setP(float);
	void setI(float);
	void setD(float);
	void setF(float);

private:
	SpeedController* shooter_wheel;

	static const float RPM_PRESETS[];
	static const float SPEED_PRESETS[];
};

#endif
