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

		int port = 1;
		victor = new VictorSP(port);

		while (port <= 13 && IsAutonomous() && IsEnabled())
		{
			if (timer->HasPeriodPassed(1.0))
			{
				victor->Set(-1.0);
			}
			else
			{
				victor->Set(1.0);
			}


			if (timer->HasPeriodPassed(2.0))
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

	void OperatorControl() // Teleop
	{
		VictorSP* victor1 = new VictorSP(1);
		VictorSP* victor2 = new VictorSP(2);
		VictorSP* victor3 = new VictorSP(3);
		VictorSP* victor4 = new VictorSP(4);
		VictorSP* victor5 = new VictorSP(5);
		VictorSP* victor6 = new VictorSP(6);
		VictorSP* victor7 = new VictorSP(7);
		VictorSP* victor8 = new VictorSP(8);
		VictorSP* victor9 = new VictorSP(9);
		VictorSP* victor10 = new VictorSP(10);
		VictorSP* victor11 = new VictorSP(11);
		VictorSP* victor_1= new VictorSP(12);
		VictorSP* victor_2 = new VictorSP(13);
		while (IsOperatorControl() && IsEnabled())
		{
			if (joystick1->GetRawButton(1))
			{
				victor1->Set(1.0);
			}
			else
			{
				victor1->Set(0.0);
			}
			if (joystick1->GetRawButton(2))
			{
				victor2->Set(1.0);
			}
			else
			{
				victor2->Set(0.0);
			}
			if (joystick1->GetRawButton(3))
			{
				victor3->Set(1.0);
			}
			else
			{
				victor3->Set(0.0);
			}
			if (joystick1->GetRawButton(4))
			{
				victor4->Set(1.0);
			}
			else
			{
				victor4->Set(0.0);
			}
			if (joystick1->GetRawButton(5))
			{
				victor5->Set(1.0);
			}
			else
			{
				victor5->Set(0.0);
			}
			if (joystick1->GetRawButton(6))
			{
				victor6->Set(1.0);
			}
			else
			{
				victor6->Set(0.0);
			}
			if (joystick1->GetRawButton(7))
			{
				victor7->Set(1.0);
			}
			else
			{
				victor7->Set(0.0);
			}
			if (joystick1->GetRawButton(8))
			{
				victor8->Set(1.0);
			}
			else
			{
				victor8->Set(0.0);
			}
			if (joystick1->GetRawButton(9))
			{
				victor9->Set(1.0);
			}
			else
			{
				victor9->Set(0.0);
			}
			if (joystick1->GetRawButton(10))
			{
				victor10->Set(1.0);
			}
			else
			{
				victor10->Set(0.0);
			}
			if (joystick1->GetRawButton(11))
			{
				victor11->Set(1.0);
			}
			else
			{
				victor11->Set(0.0);
			}
			if (joystick2->GetRawButton(12))
			{
				victor_1->Set(1.0);
			}
			else
			{
				victor_1->Set(0.0);
			}
			if (joystick2->GetRawButton(13))
			{
				victor_2->Set(1.0);
			}
			else
			{
				victor_2->Set(0.0);
			}
		}
	}

	void Test()
	{

	}
};

START_ROBOT_CLASS(Robot)
