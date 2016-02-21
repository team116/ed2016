#include "WPILib.h"

#define MOTOR_COUNT 13

class Robot: public SampleRobot
{
	Joystick* joystick1;
	Joystick* joystick2;

	VictorSP* victors[MOTOR_COUNT];

public:
	Robot()
	{
		joystick1 = new Joystick(0);
		joystick2 = new Joystick(1);

		for (int i = 0; i < MOTOR_COUNT; ++i)
		{
			victors[i] = new VictorSP(i);
		}
	}

	void RobotInit()
	{
	}

	void Autonomous() // Automatically go through every single motor, forward and backwards for 1 second
	{
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

	}
};

START_ROBOT_CLASS(Robot)
