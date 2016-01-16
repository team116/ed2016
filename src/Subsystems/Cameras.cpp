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

	cameraRunning = -1;
}

void Cameras::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

bool Cameras::StopCamera(int cameraNum) {
	if(cameraRunning != -1){
		if (cameraNum == 1) {
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
		} else if (cameraNum == 0) {
			IMAQdxStopAcquisition(sessionCam0);
			imaqError = IMAQdxCloseCamera(sessionCam0);
			if (imaqError != IMAQdxErrorSuccess) {
				DriverStation::ReportError(
						"cam0 IMAQdxCloseCamera error: "
								+ std::to_string((long) imaqError) + "\n");
				return (kError);
			}

		}
		cameraRunning = -1;
	}
	return (kOk);
}

bool Cameras::StartCamera(int cameraNum) {
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
					"cam1 IMAQdxConfigureGrab error: "
							+ std::to_string((long) imaqError) + "\n");
			return (kError);
		}
		// acquire images
		IMAQdxStartAcquisition(sessionCam1);
		cameraRunning = 1;

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
		cameraRunning = 0;

	}

	if(cameraNum == 0){
		imaqError = IMAQdxGrab(sessionCam0, frameCam0, true, NULL);
	}
	else if(cameraNum == 1){
		imaqError = IMAQdxGrab(sessionCam1, frameCam1, true, NULL);
	}
	if (imaqError != IMAQdxErrorSuccess) {
		DriverStation::ReportError(
				"cam0 IMAQdxGrab error: "
						+ std::to_string((long) imaqError) + "\n");
	} else {
		CameraServer::GetInstance()->SetImage(frameCam0);
	}
	return (kOk);
}

Cameras* Cameras::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Cameras();
	}
	return INSTANCE;
}
