#include <Log.h>
#include <WPILib.h>

#define MOTOR_COUNT 13
#define AUTO_SWITCH_COUNT 3

class Robot: public SampleRobot
{
	Joystick* joystick1;
	Joystick* joystick2;

	VictorSP* victors[MOTOR_COUNT];

	AnalogInput* auto_switches[AUTO_SWITCH_COUNT];

	Log* log;

public:
	Robot()
	{
		log = Log::getInstance();

		joystick1 = new Joystick(0);
		joystick2 = new Joystick(1);

		for (int i = 0; i < MOTOR_COUNT; ++i)
		{
			victors[i] = new VictorSP(i);
		}

		for (int i = 0; i < AUTO_SWITCH_COUNT; ++i)
		{
			auto_switches[i] = new AnalogInput(i + 4);
		}
	}

	void logAutoSwitches()
	{
		for (int i = 0; i < AUTO_SWITCH_COUNT; ++i)
		{
			log->write(Log::INFO_LEVEL, "Auto Switch %d, voltage: %f, port: %d", i, auto_switches[i]->GetVoltage(), auto_switches[i]->GetChannel());
		}
	}

	void RobotInit()
	{
	}

	void Autonomous() // Automatically go through every single motor, forward and backwards for 1 second
	{
		logAutoSwitches();

		Timer* timer = new Timer();
		timer->Start();
		timer->Reset();

		int i = 0;
		while (i <= 13 && IsAutonomous() && IsEnabled())
		{
			if (timer->Get() > 1.0)
			{
				victors[i]->Set(-1.0);
			}
			else
			{
				victors[i]->Set(1.0);
			}

			if (timer->Get() > 2.0)
			{
				victors[i]->Set(0.0);
				++i;
				timer->Reset();
			}
		}
	}

	void OperatorControl()
	{
		logAutoSwitches();

		JoystickButton* buttons[13];
		JoystickButton reverse_button(joystick1, 11);

		int i;
		for (i = 0; i < 13; ++i)
		{
			if (i < 10)
			{
				buttons[i] = new JoystickButton(joystick1, i + 1);
			}
			else
			{
				buttons[i] = new JoystickButton(joystick2, i - 9);
			}
		}

		while (IsOperatorControl() && IsEnabled())
		{
			for (i = 0; i < 13; ++i)
			{
				if (buttons[i]->Get())
				{
					if (reverse_button.Get())
					{
						victors[i]->Set(-1.0);
					}
					else
					{
						victors[i]->Set(1.0);
					}
				}
				else
				{
					victors[i]->Set(0.0);
				}
			}
		}

		for (i = 0; i < 13; ++i)
		{
			delete buttons[i];
		}
	}

	void Test()
	{
		logAutoSwitches();

		static char log[255];
		while (IsTest() && IsEnabled())
		{
			snprintf(log, 255, "Switch0 volts: %f, Switch1 volts: %f, Switch2 volts: %f",
					auto_switches[0]->GetVoltage(), auto_switches[1]->GetVoltage(), auto_switches[2]->GetVoltage());
			DriverStation::ReportError(log);
		}
	}
};

START_ROBOT_CLASS(Robot)
