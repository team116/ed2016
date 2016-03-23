#ifndef Yellow_H
#define Yellow_H

#include <Commands/Subsystem.h>
#include <Log.h>
#include <RobotMap.h>
#include <WPILib.h>

class Intake: public PIDSubsystem
{
public:
	static const int ANGLE_PRESET_COUNT;
	static float getAnglePreset(int index);

	Intake();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();

	void setIntakeDirection(Utils::HorizontalDirection);
	void setIntakeAngleDirection(Utils::VerticalDirection);

	bool isPIDEnabled();
	float getP();
	float getI();
	float getD();
	float getF();
	void setP(float);
	void setI(float);
	void setD(float);
	void setF(float);

private:
	SpeedController* intake_roller;
	SpeedController* intake_angle;

	static float* ANGLE_PRESETS;

	void setSpeed(float);

	Log* log;

};

#endif
