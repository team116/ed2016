#ifndef SelectCamera_H
#define SelectCamera_H

#include <CommandBase.h>
#include <WPILib.h>
#include <Subsystems/Cameras.h>

class SelectCamera: public CommandBase
{
public:
	SelectCamera(int cam);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	int camera_num;

	bool is_finished;
};

#endif
