#ifndef CheckManualOverrides_H
#define CheckManualOverrides_H

#include <WPILib.h>

namespace CheckManualOverrides
{
	void initialize();
	void process();

	void requestPIDEnable(PIDSubsystem* subsystem, bool enable);
};

#endif
