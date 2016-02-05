#include <RobotMap.h>

namespace Utils
{
	int voltageConversion(const float voltage, const int voltage_levels, const float max_voltage)
	{
		float output = (voltage / max_voltage) * ((float) voltage_levels - 1); // needs to be rounded, never do == w/ decimals
		return (int) (output + 0.5); // round the value
	}

}
