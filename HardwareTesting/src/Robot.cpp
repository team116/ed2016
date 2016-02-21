#include "WPILib.h"

class Robot: public SampleRobot
{
	Joystick* joystick1;
	Joystick* joystick2;
public:
	Robot()
	{
		joystick1 = new Joystick(1);
		joystick2 = new Joystick(2);
	}

	void RobotInit()
	{
	}

	void Autonomous() // Automatically go through every single motor, forward and backwards for 1 second
	{
		VictorSP* victor;
		Timer* timer = new Timer();
		timer->Start();
		timer->Reset();

		int port = 0;
		victor = new VictorSP(port);

		while (port <= 13 && IsAutonomous() && IsEnabled())
		{
			if (timer->Get() > 1.0)
			{
				victor->Set(-1.0);
			}
			else
			{
				victor->Set(1.0);
			}


			if (timer->Get() > 2.0)
			{
				++port;
				victor->Set(0.0);
				timer->Reset();
				delete victor;
				victor = new VictorSP(port);
			}
		}

		delete victor;
	}

	void OperatorControl()
	{
		VictorSP* victors[13];
		JoystickButton* buttons[13];

		Joystick joystick1(0);
		Joystick joystick2(1);
		JoystickButton reverse_button(&joystick1, 11);

		int i;
		for (i = 0; i < 13; ++i)
		{
			if (i < 10)
			{
				buttons[i] = new JoystickButton(&joystick1, i + 1);
			}
			else
			{
				buttons[i] = new JoystickButton(&joystick2, i - 9);
			}
			victors[i] = new VictorSP(i);
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
			delete victors[i];
			delete buttons[i];
		}
	}

	void Test()
	{

	}
};

START_ROBOT_CLASS(Robot)
