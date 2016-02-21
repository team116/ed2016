#include <Log.h>
#include <RobotMap.h>

namespace Utils
{
	RobotType getRobotType()
	{
		return RobotType::ED2016_BOT;
	}

	SpeedController* constructMotor(unsigned int port)
	{
		if (getRobotType() == RobotType::ANDERSON_BOT)
		{
			return new CANTalon(port);
		}
		else if (getRobotType() == RobotType::ED2016_BOT)
		{
			return new VictorSP(port);
		}
		else
		{
			Log::getInstance()->write(Log::ERROR_LEVEL, "Unable to construct motor because of unknown motor type");
			DriverStation::ReportError("Unable to construct motor because of unknown motor type\n");
			return nullptr;
		}
	}

	int voltageConversion(const float voltage, const int voltage_levels, const float max_voltage)
	{
		float output = (voltage / max_voltage) * ((float) voltage_levels - 1); // needs to be rounded, never do == w/ decimals
		return (int) (output + 0.5); // round the value
	}


	float boundaryCheck(float target, float min, float max)
	{
		if(target > max)
		{
			return max;
		}
		if (target < min)
		{
			return min;
		}
		return target;
	}
}
