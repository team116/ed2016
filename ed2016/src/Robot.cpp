#include <NAVX/AHRS.h>
#include <WPILib.h>
#include <RobotMap.h>
#include <Commands/Command.h>
#include <CommandBase.h>
#include <Autonomous.h>
#include <Commands/Autonomous/CrossDefense.h>
#include <Commands/Autonomous/DoNothing.h>

using namespace Autonomous;
using namespace Utils;

class Robot: public IterativeRobot
{
private:
	Command* auto_command;
	SendableChooser *chooser;

	AnalogInput* goal_switch;
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

		voltageConversion(goal_switch->GetVoltage(), 3, 5.0);
		voltageConversion(defense_switch->GetVoltage(), 8, 5.0);

		int AutoPlays = pow(8, 0)*voltageConversion(goal_switch->GetVoltage(), 3, 5.0) + pow(8, 2)*voltageConversion(defense_switch->GetVoltage(), 8, 5.0);

		/*switch ((AllAutoPlays)AutoPlays)
		{
		case AllAutoPlays::NOSHOOTING_DEFPORTCULLIS:
			auto_command = new CrossDefense(Defense::PORTCULLIS);
			break;
		case AllAutoPlays::NOSHOOTING_DEFCHEVALDEFRISES:
			auto_command = new CrossDefense(Defense::CHEVAL_DE_FRISES);
			break;
		case AllAutoPlays::NOSHOOTING_DEFMOAT:
			auto_command = new CrossDefense(Defense::MOAT);
			break;
		case AllAutoPlays::NOSHOOTING_DEFRAMPARTS:
			auto_command = new CrossDefense(Defense::RAMPARTS);
			break;
		case AllAutoPlays::NOSHOOTING_DEFDRAWBRIDGE:
			auto_command = new CrossDefense(Defense::DRAWBRIDGE);
			break;
		case AllAutoPlays::NOSHOOTING_DEFSALLYPORT:
			auto_command = new CrossDefense(Defense::SALLY_PORT);
			break;
		case AllAutoPlays::NOSHOOTING_DEFROCKWALL:
			auto_command = new CrossDefense(Defense::ROCK_WALL);
			break;
		case AllAutoPlays::NOSHOOTING_DEFROUGHTERRAIN:
			auto_command = new CrossDefense(Defense::ROUGH_TERRAIN);
			break;
		case AllAutoPlays::SHOOTINGLOW_DEFPORTCULLIS:
			auto_command = new CrossDefense(Defense::PORTCULLIS);
			break;
		case AllAutoPlays::SHOOTINGLOW_DEFCHEVALDEFRISES:
			auto_command = new CrossDefense(Defense::CHEVAL_DE_FRISES);
			break;
		case AllAutoPlays::SHOOTINGLOW_DEFMOAT:
			auto_command = new CrossDefense(Defense::MOAT);
			break;
		case AllAutoPlays::SHOOTINGLOW_DEFRAMPARTS:
			auto_command = new CrossDefense(Defense::RAMPARTS);
			break;
		case AllAutoPlays::SHOOTINGLOW_DEFDRAWBRIDGE:
			auto_command = new CrossDefense(Defense::DRAWBRIDGE);
			break;
		case AllAutoPlays::SHOOTINGLOW_DEFSALLYPORT:
			auto_command = new CrossDefense(Defense::SALLY_PORT);
			break;
		case AllAutoPlays::SHOOTINGLOW_DEFROCKWALL:
			auto_command = new CrossDefense(Defense::ROCK_WALL);
			break;
		case AllAutoPlays::SHOOTINGLOW_DEFROUGHTERRAIN:
			auto_command = new CrossDefense(Defense::ROUGH_TERRAIN);
			break;
		case AllAutoPlays::SHOOTINGHIGH_DEFPORTCULLIS:
			auto_command = new CrossDefense(Defense::PORTCULLIS);
			break;
		case AllAutoPlays::SHOOTINGHIGH_DEFCHEVALDEFRISES:
			auto_command = new CrossDefense(Defense::CHEVAL_DE_FRISES);
			break;
		case AllAutoPlays::SHOOTINGHIGH_DEFMOAT:
			auto_command = new CrossDefense(Defense::MOAT);
			break;
		case AllAutoPlays::SHOOTINGHIGH_DEFRAMPARTS:
			auto_command = new CrossDefense(Defense::RAMPARTS);
			break;
		case AllAutoPlays::SHOOTINGHIGH_DEFDRAWBRIDGE:
			auto_command = new CrossDefense(Defense::DRAWBRIDGE);
			break;
		case AllAutoPlays::SHOOTINGHIGH_DEFSALLYPORT:
			auto_command = new CrossDefense(Defense::SALLY_PORT);
			break;
		case AllAutoPlays::SHOOTINGHIGH_DEFROCKWALL:
			auto_command = new CrossDefense(Defense::ROCK_WALL);
			break;
		case AllAutoPlays::SHOOTINGHIGH_DEFROUGHTERRAIN:
			auto_command = new CrossDefense(Defense::ROUGH_TERRAIN);
			break;
		default:
			auto_command = new DoNothing();
		} */
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

