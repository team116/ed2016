#include <Subsystems/Cameras.h>
#include <RobotMap.h>

Cameras* Cameras::INSTANCE = nullptr;

const bool kError = false;
const bool kOk = true;

Cameras::Cameras() :
		Subsystem("Cameras")
{
	frameCam0 = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	frameCam1 = imaqCreateImage(IMAQ_IMAGE_RGB, 0);

	camera_running = -1;

	//-1074360316
}

void Cameras::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

bool Cameras::StopCamera(int cameraNum)
{
	if (cameraNum == 1 && camera_running == 1) {
		// stop image acquisition
		IMAQdxStopAcquisition(sessionCam1);
		//the camera name (ex "cam0") can be found through the roborio web interface
		imaqError = IMAQdxCloseCamera(sessionCam1);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"cam1 IMAQdxCloseCamera error: "
							+ std::to_string((long) imaqError) + "\n");
			return (kError);
		}
	} else if (cameraNum == 0 && camera_running == 0) {
		IMAQdxStopAcquisition(sessionCam0);
		imaqError = IMAQdxCloseCamera(sessionCam0);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"cam0 IMAQdxCloseCamera error: "
							+ std::to_string((long) imaqError) + "\n");
			return (kError);
		}

	}
	return (kOk);
}

bool Cameras::StartCamera(int cameraNum)
{
	if(camera_running >= 0)
	{
		StopCamera(camera_running);
	}
	if (cameraNum == 1) {

		imaqError = IMAQdxOpenCamera("cam1",
				IMAQdxCameraControlModeController, &sessionCam1);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"cam1 IMAQdxOpenCamera error: "
							+ std::to_string((long) imaqError) + "\n");
			return (kError);
		}
		imaqError = IMAQdxConfigureGrab(sessionCam1);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"cam0 IMAQdxConfigureGrab error: "
							+ std::to_string((long) imaqError) + "\n");
			return (kError);
		}
		// acquire images
		IMAQdxStartAcquisition(sessionCam1);
		camera_running = 1;

	} else if (cameraNum == 0) {
		imaqError = IMAQdxOpenCamera("cam0",
				IMAQdxCameraControlModeController, &sessionCam0);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"cam0 IMAQdxOpenCamera error: "
							+ std::to_string((long) imaqError) + "\n");
			return (kError);
		}
		imaqError = IMAQdxConfigureGrab(sessionCam0);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"cam0 IMAQdxConfigureGrab error: "
							+ std::to_string((long) imaqError) + "\n");
			return (kError);
		}
		// acquire images
		IMAQdxStartAcquisition(sessionCam0);
		camera_running = 0;

	}
	return (kOk);
}

void Cameras::RunCamera(int cameraNum)
{
	if(cameraNum == 0){
		imaqError = IMAQdxGrab(sessionCam0, frameCam0, true, NULL);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"cam0 IMAQdxGrab error: "
							+ std::to_string((long) imaqError) + "\n");
		} else {
			CameraServer::GetInstance()->SetImage(frameCam0);
		}
	}
	else if(cameraNum == 1){
		imaqError = IMAQdxGrab(sessionCam1, frameCam1, true, NULL);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"cam1 IMAQdxGrab error: "
							+ std::to_string((long) imaqError) + "\n");
		} else {
			CameraServer::GetInstance()->SetImage(frameCam1);
		}
	}
}

int Cameras::GetRunningCamera()
{
	return camera_running;
}

Cameras* Cameras::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Cameras();
	}
	return INSTANCE;
}
