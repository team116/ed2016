#include <NAVX/AHRS.h>
#include <WPILib.h>
#include <RobotMap.h>
#include <Commands/Command.h>
#include <CommandBase.h>
#include <Autonomous.h>
#include <Commands/Autonomous/CrossDefense.h>
#include <Commands/Autonomous/DoNothing.h>
#include <Commands/Autonomous/MoveToDefense.h>
#include <Commands/Autonomous/CrossDefAndShoot.h>
#include <Commands/Autonomous/SpyBoxShoot.h>
#include <Commands/Autonomous/SpyBoxShootAndReach.h>
#include <Commands/TogglePID.h>
#include <Log.h>
#include <Subsystems/ShooterPitch.h>

using namespace Autonomous;
using namespace Utils;

class Robot: public IterativeRobot
{
private:
	Command* auto_command;

	AnalogInput* shoot_switch;
	AnalogInput* position_switch;
	AnalogInput* defense_switch;

	Log* log;

	void RobotInit()
	{
		CommandBase::init();

		shoot_switch = new AnalogInput(RobotPorts::AUTONOMOUS_NAVX_A);
		position_switch = new AnalogInput(RobotPorts::AUTONOMOUS_NAVX_B);
		defense_switch = new AnalogInput(RobotPorts::AUTONOMOUS_NAVX_C);

		log = Log::getInstance();
	}

	/**
     * This function is called once each time the robot enters Disabled mode.
     * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
     */
	void DisabledInit()
	{
		Scheduler::GetInstance()->AddCommand(new TogglePID(false));
	}

	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString code to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional commands to the chooser code above (like the commented example)
	 * or additional comparisons to the if-else structure below with additional strings & commands.
	 */
	void AutonomousInit()
	{
		float shoot_voltage = shoot_switch->GetVoltage();
		int shoot_value = voltageConversion(shoot_voltage, 3, 5.0);

		float position_voltage = position_switch->GetVoltage();
		int position_value = voltageConversion(position_voltage, 6, 5.0);

		float defense_voltage = defense_switch->GetVoltage();
		int defense_value = voltageConversion(defense_voltage, 8, 5.0);

		log->write(Log::TRACE_LEVEL, " Shooter Auto Switch value: %d, voltage: %f, port: %d", shoot_value, shoot_voltage, (int)shoot_switch->GetChannel());
		log->write(Log::TRACE_LEVEL, "Position Auto Switch value: %d, voltage: %f, port: %d", position_value, position_voltage, (int)position_switch->GetChannel());
		log->write(Log::TRACE_LEVEL, " Defense Auto Switch value: %d, voltage: %f, port: %d", defense_value, defense_voltage, (int)defense_switch->GetChannel());

		shoot_value = 0;
		position_value = 1;
		defense_value = 0;

		if (shoot_value == 0 && position_value == 0 && defense_value == 0)
		{
			auto_command = new DoNothing();
		}
		//MoveToDefense Plays
		else if (shoot_value == 0 && position_value != 0 && defense_value == 0)
		{
			auto_command = new MoveToDefense();
		}
		//CrossDefense plays
				//no shooting, position 1, various defenses
		else if (shoot_value == 0 && position_value != 0  && defense_value != 0)
		{
			auto_command = new CrossDefense((Defense)defense_value);
		}
		//SpyBoxShoot
		else if ((shoot_value == 1 || shoot_value == 2) && position_value == 0 && defense_value == 0)
		{
			auto_command = new SpyBoxShoot((Goals)shoot_value);
		}
		//SpyBoxShootAndReach
		else if ((shoot_value == 1 || shoot_value == 2) && position_value == 0 && defense_value != 0)
		{
			auto_command = new SpyBoxShootAndReach((Goals)shoot_value);
		}
		//CrossDefAndShoot plays
		else if ((shoot_value == 1 || shoot_value == 2) && position_value != 0 && defense_value != 0)
		{
			auto_command = new CrossDefAndShoot((Defense)defense_value, (Goals)shoot_value, position_value);
		}
		else
		{
			auto_command = new DoNothing();
		}
		//Failsafe
		//auto_command->Start();
		Scheduler::GetInstance()->AddCommand(auto_command);
	}

	void AutonomousPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit()
	{
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (auto_command != NULL)
			auto_command->Cancel();
		DriverStation::ReportError("Starting Robot " + std::to_string(CommandBase::oi->getPIDEnableSwitch()));
		//CommandBase::sensors->zeroShooterPitch();
		Scheduler::GetInstance()->AddCommand(new TogglePID(CommandBase::oi->getPIDEnableSwitch()));
	}

	void TeleopPeriodic()
	{
		Scheduler::GetInstance()->Run();
		CommandBase::oi->process();
		CommandBase::shooter_pitch->checkLimits();
		log->write(Log::TRACE_LEVEL, "Robot Angle: %f Shooter Pitch: %f", CommandBase::sensors->robotAngle(), CommandBase::sensors->shooterAngle());
	}

	void TestInit()
	{
		DriverStation::ReportError("my message");
		float shoot_voltage = shoot_switch->GetVoltage();
		int shoot_value = voltageConversion(shoot_voltage, 3, 5.0);

		float position_voltage = position_switch->GetVoltage();
		int position_value = voltageConversion(position_voltage, 6, 5.0);

		float defense_voltage = defense_switch->GetVoltage();
		int defense_value = voltageConversion(defense_voltage, 8, 5.0);

		log->write(Log::INFO_LEVEL, " Shooter Auto Switch value: %d, voltage: %f, port: %d", shoot_value, shoot_voltage, (int)shoot_switch->GetChannel());
		log->write(Log::INFO_LEVEL, "Position Auto Switch value: %d, voltage: %f, port: %d", position_value, position_voltage, (int)position_switch->GetChannel());
		log->write(Log::INFO_LEVEL, " Defense Auto Switch value: %d, voltage: %f, port: %d", defense_value, defense_voltage, (int)defense_switch->GetChannel());
	}

	void TestPeriodic()
	{
		LiveWindow::GetInstance()->Run();

		/*
		static char log[255];
		snprintf(log, 255, "Shoot volt: %f, Pos volt: %f, Def volt: %f", shoot_switch->GetVoltage(), position_switch->GetVoltage(), defense_switch->GetVoltage());
		DriverStation::ReportError(log);
		*/
	}
};

START_ROBOT_CLASS(Robot)

