#include <Subsystems/Cameras.h>
#include <RobotMap.h>
#include <Commands/SelectCamera.h>

Cameras* Cameras::INSTANCE = nullptr;

const bool kError = false;
const bool kOk = true;
const int IMAGE_WIDTH = 320;
const int IMAGE_HEIGHT = 240;

Cameras::Cameras() :
		Subsystem("Cameras")
{
	front_cam_frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	back_cam_frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);

	camera_running = CameraDirection::NONE;

	grip = NetworkTable::GetTable("GRIP");

	//-1074360316
}

void Cameras::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand();
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

bool Cameras::StopCamera(CameraDirection camera_dir)
{
	if (camera_dir == CameraDirection::BACK && camera_running == CameraDirection::BACK) {
		// stop image acquisition
		IMAQdxStopAcquisition(back_cam_session);
		//the camera name (ex "cam0") can be found through the roborio web interface
		imaqError = IMAQdxCloseCamera(back_cam_session);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"back cam IMAQdxCloseCamera error: "
							+ std::to_string((long) imaqError) + "\n");
			return (kError);
		}
	} else if (camera_dir == CameraDirection::FRONT && camera_running == CameraDirection::FRONT) {
		IMAQdxStopAcquisition(front_cam_session);
		imaqError = IMAQdxCloseCamera(front_cam_session);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"front cam IMAQdxCloseCamera error: "
							+ std::to_string((long) imaqError) + "\n");
			return (kError);
		}

	}
	return (kOk);
}

bool Cameras::StartCamera(CameraDirection camera_dir)
{
	if(camera_running != CameraDirection::NONE)
	{
		StopCamera(camera_running);
	}
	if (camera_dir == CameraDirection::BACK) {

		imaqError = IMAQdxOpenCamera("cam1",
				IMAQdxCameraControlModeController, &back_cam_session);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"back cam IMAQdxOpenCamera error: "
							+ std::to_string((long) imaqError) + "\n");
			return (kError);
		}
		imaqError = IMAQdxConfigureGrab(back_cam_session);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"back cam IMAQdxConfigureGrab error: "
							+ std::to_string((long) imaqError) + "\n");
			return (kError);
		}
		// acquire images
		IMAQdxStartAcquisition(back_cam_session);
		camera_running = CameraDirection::BACK;

	} else if (camera_dir == CameraDirection::FRONT) {
		imaqError = IMAQdxOpenCamera("cam0",
				IMAQdxCameraControlModeController, &front_cam_session);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"front cam IMAQdxOpenCamera error: "
							+ std::to_string((long) imaqError) + "\n");
			return (kError);
		}
		imaqError = IMAQdxConfigureGrab(front_cam_session);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"front cam IMAQdxConfigureGrab error: "
							+ std::to_string((long) imaqError) + "\n");
			return (kError);
		}
		// acquire images
		IMAQdxStartAcquisition(front_cam_session);
		camera_running = CameraDirection::FRONT;

	}
	return (kOk);
}

void Cameras::RunCamera(CameraDirection camera_dir)
{
	if(camera_dir == CameraDirection::FRONT){
		imaqError = IMAQdxGrab(front_cam_session, front_cam_frame, true, NULL);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"front cam IMAQdxGrab error: "
							+ std::to_string((long) imaqError) + "\n");
		} else {
			CameraServer::GetInstance()->SetImage(front_cam_frame);
		}
	}
	else if(camera_dir == CameraDirection::BACK){
		imaqError = IMAQdxGrab(back_cam_session, back_cam_frame, true, NULL);
		if (imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"back cam IMAQdxGrab error: "
							+ std::to_string((long) imaqError) + "\n");
		} else {
			CameraServer::GetInstance()->SetImage(back_cam_frame);
		}
	}
}

int Cameras::GetRunningCamera()
{
	return camera_running;
}

bool Cameras::canSeeGoal()
{
	if(grip->GetNumberArray("vision_contours/area", llvm::ArrayRef<double>()).size() > 0) {
		DriverStation::ReportError("Can see vision target\n");
		return true;
	}
	return false;
}

float Cameras::GetTargetX()
{
	if(grip->GetNumberArray("vision_contours/centerX", llvm::ArrayRef<double>()).size() > 0) {
		return grip->GetNumberArray("vision_contours/centerX", llvm::ArrayRef<double>())[0];
	}
	return 116; //If there is no target in view...
}

float Cameras::GetTargetY()
{
	if(grip->GetNumberArray("vision_contours/centerY", llvm::ArrayRef<double>()).size() > 0) {
		return grip->GetNumberArray("vision_contours/centerY", llvm::ArrayRef<double>())[0];
	}
	return 116; //If there is no target in view...
}

Cameras* Cameras::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Cameras();
	}
	return INSTANCE;
}
