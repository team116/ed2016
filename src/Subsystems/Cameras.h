#ifndef Cameras_H
#define Cameras_H

#include <Commands/Subsystem.h>
#include <WPILib.h>

class Cameras: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	IMAQdxSession sessionCam0;
	IMAQdxSession sessionCam1;

	int cameraRunning;

	Image *frameCam0;
	Image *frameCam1;

	IMAQdxError imaqError;

	static Cameras* INSTANCE;
public:
	Cameras();
	void InitDefaultCommand();

	bool StopCamera(int cameraNum);
	bool StartCamera(int cameraNum);
	void RunCamera(int cameraNum);

	static Cameras* getInstance();
};

#endif
