#ifndef SelectCamera_H
#define SelectCamera_H

#include <CommandBase.h>
#include <WPILib.h>
#include <Subsystems/Cameras.h>

class SelectCamera: public CommandBase
{
public:
	SelectCamera(Cameras::CameraDirection direction);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	Cameras::CameraDirection camera_direction;

	bool is_finished;
};

#endif
