#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
#include <RobotMap.h>
#include <WPILib.h>


class Shooter: public PIDSubsystem
{
public:
	Shooter();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();

	void setSpeed(float speed);

	float getRPMPreset(int preset); // 0 to 5
	float getSpeedPreset(int preset); // 0 to 5

	float getSpeedToTarget(float angle);

	float getMotorSpeed();

	float getP();
	float getI();
	float getD();
	float getF();
	float getIzone();
	void setP(float);
	void setI(float);
	void setD(float);
	void setF(float);

	bool OnTarget();

	void setRPM(float);

private:
	SpeedController* shooter_wheel;

	static const float RPM_PRESETS[];
	static const float SPEED_PRESETS[];

	float speed;

	float tolerance;
};

#endif
