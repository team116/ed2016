#include <RobotMap.h>

int Utils::voltageConversion(const float voltage, const int voltage_levels, const float max_voltage)
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
