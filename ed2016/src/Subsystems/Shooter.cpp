#include <Commands/RunShooterWheels.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/ShooterPitch.h>
#include <RobotMap.h>
#include <Subsystems/Sensors.h>
#include <Log.h>
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"

const float Shooter::RPM_PRESETS[] = {
	1000.0,
	1300.0,
	1600.0,
	1900.0,
	2200.0,
	2500.0
};

const float Shooter::SPEED_PRESETS[] = {
	0.5,
	0.6,
	0.7,
	0.8,
	0.9,
	1.0
};

const int Shooter::CYCLES_FOR_ONTARGET = 5;
const int Shooter::ONTARGET_TOLERANCE = 25;
const float Shooter::SHOOT_VELOCITY = 9.2;//m/s Tested to work on max rpm preset (2500 rpm), should work on the next one down as well (2200 rpm)

Shooter::Shooter() : PIDSubsystem("Shooter", 0.001, 0.0, 0.001, 0.00034)
{
	shooter_wheel = Utils::constructMotor(RobotPorts::SHOOTER_MOTOR);

	tolerance = 10;

	SetPIDSourceType(PIDSourceType::kRate);
	GetPIDController()->SetContinuous(false);

	SetInputRange(0, RPM_PRESETS[5]);
	SetAbsoluteTolerance(tolerance);
	SetOutputRange(0.0,1.0);

	speed = 0;

	cycles_within_tolerance = 0;
}

void Shooter::InitDefaultCommand()
{
	SetDefaultCommand(new RunShooterWheels());
}

double Shooter::ReturnPIDInput()
{
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;
	//CommandBase::log->write(Log::DEBUG_LEVEL, "");
	//CommandBase::log->write(Log::DEBUG_LEVEL, "Shooter Rate: %f Target: %f P: %F I: %F D: %F", CommandBase::sensors->speedShooterWheel(), GetSetpoint(), GetPIDController()->GetP(), GetPIDController()->GetI(), GetPIDController()->GetD());
	//CommandBase::log->write(Log::DEBUG_LEVEL, "OnTarget: %d", OnTarget());
	//DriverStation::ReportError("");
	//DriverStation::ReportError("Input: " + std::to_string(CommandBase::sensors->speedShooterWheel()) + " Target: " + std::to_string(GetSetpoint()) + " P: " + std::to_string(getP()) + " I: " + std::to_string(getI()) + " D: " + std::to_string(getD()));
	return CommandBase::sensors->speedShooterWheel();
}

void Shooter::UsePIDOutput(double output)
{
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	if(isPIDEnabled()) {
		//CommandBase::log->write(Log::DEBUG_LEVEL, "Shooter Output: %f Cycles: %d OnTarget: %d", output, cycles_within_tolerance, OnTarget());
		//CommandBase::log->write(Log::DEBUG_LEVEL, "");
		//DriverStation::ReportError("Output: " + std::to_string(output) + " OnTarget: " + std::to_string(OnTarget()));
		setSpeed(output);
		checkTarget();
	}
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::setSpeed(float speed)
{
	//DriverStation::ReportError("Speed: " + std::to_string(speed));
	shooter_wheel->Set(speed);
}

void Shooter::setRPM(float rpm)
{
	SetSetpoint(rpm);
	if(!isPIDEnabled())
	{
		float offset = (RPM_PRESETS[5] - RPM_PRESETS[0]) / 10; //Half of the number between each preset
		int preset = -1;
		for(int x = 0; x < 6; x++)
		{
			if(rpm < (RPM_PRESETS[x] + offset))
			{
				preset = x;
				break;
			}
		}
		if(preset != -1)
		{
			setSpeed(SPEED_PRESETS[preset]);
		}
		else
		{
			setSpeed(SPEED_PRESETS[5]);
		}
	}
}

float Shooter::getRPMPreset(int preset)
{
	return RPM_PRESETS[preset];
}

float Shooter::getSpeedPreset(int preset)
{
	return SPEED_PRESETS[preset];
}

//Returns necessary shooter rpm speed
//Angle of ball launch, NOT angle of shooter. Should be angle perpendicular to shooter
float Shooter::getSpeedToTarget(float angle)
{
	//sqrt(-2gy)/sin(theta) * 60 / (2*pi*r)
	return (sqrt(1960 * CommandBase::shooter_pitch->SHOOTER_TO_TARGET_HEIGHT) / sin(angle) * 60) / (10.16 * M_PI);
}

float Shooter::getMotorSpeed()
{
	return shooter_wheel->Get();
}

bool Shooter::isPIDEnabled()
{
	return GetPIDController()->IsEnabled();
}

float Shooter::getP()
{
	return GetPIDController()->GetP();
}
float Shooter::getI()
{
	return GetPIDController()->GetI();
}
float Shooter::getD()
{
	return GetPIDController()->GetD();
}
float Shooter::getF()
{
	return GetPIDController()->GetF();
}

void Shooter::setP(float p)
{
	GetPIDController()->SetPID(p, getI(), getD());
}
void Shooter::setI(float i)
{
	GetPIDController()->SetPID(getP(), i, getD());
}
void Shooter::setD(float d)
{
	GetPIDController()->SetPID(getP(), getI(), d);
}
void Shooter::setF(float f)
{
	GetPIDController()->SetPID(getP(), getI(), getD(), f);
}

bool Shooter::OnTarget()
{
	if(cycles_within_tolerance >= CYCLES_FOR_ONTARGET)
	{
		return true;
	}
	return false;
}

void Shooter::checkTarget()
{
	if(fabs(GetPIDController()->GetError()) < ONTARGET_TOLERANCE)
	{
		//Has to be in its own if statement because otherwise it would reset the cycle count every time it reached the max
		if(cycles_within_tolerance < CYCLES_FOR_ONTARGET)
		{
			cycles_within_tolerance++;
		}
	}
	else
	{
		//CommandBase::log->write(Log::DEBUG_LEVEL, "Resetting cycles. Error: %f", GetPIDController()->GetError());
		cycles_within_tolerance = 0;
	}
}
