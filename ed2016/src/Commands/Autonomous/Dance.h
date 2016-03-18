#ifndef SRC_COMMANDS_Dance_H_
#define SRC_COMMANDS_Dance_H_
#include "Commands/CommandGroup.h"
#include "WPILib.h"

class Dance: public CommandGroup {
public:
	Dance();
private:
	Timer* Bob; //Hi. I'm bob.
};

#endif /* SRC_COMMANDS_Dance_H_ */
