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

using namespace Autonomous;
using namespace Utils;

class Robot: public IterativeRobot
{
private:
	Command* auto_command;
	SendableChooser *chooser;

	AnalogInput* shoot_switch;
	AnalogInput* position_switch;
	AnalogInput* defense_switch;

	void RobotInit()
	{
		CommandBase::init();
		chooser = new SendableChooser();
		//chooser->AddDefault("Default Auto", new ExampleCommand());
		//chooser->AddObject("My Auto", new MyAutoCommand());
		SmartDashboard::PutData("Auto Modes", chooser);

		/*int var = 0;
		switch (var)
		{
		case 0:
			break;
		case 1:
			break;
		default:
		*/

	}

	/**
     * This function is called once each time the robot enters Disabled mode.
     * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
     */
	void DisabledInit()
	{
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
		/* std::string autoSelected = SmartDashboard::GetString("Auto Selector", "Default");
		if(autoSelected == "My Auto") {
			autonomousCommand.reset(new MyAutoCommand());
		} else {
			autonomousCommand.reset(new ExampleCommand());
		} */

		int shoot_value = voltageConversion(shoot_switch->GetVoltage(), 3, 5.0);
		int position_value = voltageConversion(position_switch->GetVoltage(), 6, 5.0);
		int defense_value = voltageConversion(defense_switch->GetVoltage(), 8, 5.0);

		int AutoPlays = pow(8, 0)*voltageConversion(shoot_switch->GetVoltage(), 3, 5.0) + pow(8, 1)*voltageConversion(position_switch->GetVoltage(), 6, 5.0) + pow(8, 2)*voltageConversion(defense_switch->GetVoltage(), 8, 5.0);

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
			auto_command = new CrossDefense(Defense);
		}
		//CrossDefAndShoot plays
		else if ((shoot_value == 1 || shoot_value == 2) && defense_value != 0 && position_value != 0)
		{
			auto_command = new CrossDefAndShoot((Defense)defense_value, (Goals)shoot_value, position_value);
		}


		auto_command->Start();

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
		DriverStation::ReportError("Starting Robot");
	}

	void TeleopPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void TestPeriodic()
	{
		LiveWindow::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(Robot)

