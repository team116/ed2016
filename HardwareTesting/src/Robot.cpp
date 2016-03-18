#include <Log.h>
#include <WPILib.h>

#define MOTOR_COUNT 13
#define ANALOG_SWITCH_COUNT 4
#define DIGITAL_INPUT_COUNT 10

class Robot: public SampleRobot
{
	Joystick* joystick1;
	Joystick* joystick2;

	VictorSP* victors[MOTOR_COUNT];

	AnalogInput* analog_ins[ANALOG_SWITCH_COUNT];

	DigitalInput* digital_ins[DIGITAL_INPUT_COUNT];

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

		for (int i = 0; i < ANALOG_SWITCH_COUNT; ++i)
		{
			analog_ins[i] = new AnalogInput(i);
		}

		for (int i = 0; i < DIGITAL_INPUT_COUNT; ++i)
		{
			digital_ins[i] = new DigitalInput(i);
		}

	}

	void logAutoSwitches()
	{
		for (int i = 0; i < ANALOG_SWITCH_COUNT; ++i)
		{
			log->write(Log::INFO_LEVEL, "Auto Switch %d, voltage: %f, port: %d", i, analog_ins[i]->GetVoltage(), analog_ins[i]->GetChannel());
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
			char buffer[255];
			snprintf(buffer, 255, "%d%d%d%d%d%d%d%d%d%d : %f, %f,%f,%f",
				digital_ins[0]->Get(),
				digital_ins[1]->Get(),
				digital_ins[2]->Get(),
				digital_ins[3]->Get(),
				digital_ins[4]->Get(),
				digital_ins[5]->Get(),
				digital_ins[6]->Get(),
				digital_ins[7]->Get(),
				digital_ins[8]->Get(),
				digital_ins[9]->Get(),
				analog_ins[0]->GetVoltage(),
				analog_ins[1]->GetVoltage(),
				analog_ins[2]->GetVoltage(),
				analog_ins[3]->GetVoltage());
			DriverStation::ReportError(buffer);
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
			// snprintf(log, 255, "Switch0 volts: %f, Switch1 volts: %f, Switch2 volts: %f",
			//	 	auto_switches[0]->GetVoltage(), auto_switches[1]->GetVoltage(), auto_switches[2]->GetVoltage());
		}
	}
};

START_ROBOT_CLASS(Robot)
