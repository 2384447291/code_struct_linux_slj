#include "Camera.hpp"
#include <filesystem>

void Camera::init() {
    camera.open(0);
    if (!camera.isOpened()) {
        throw std::runtime_error("Error: Camera not opened!");
    }
    camera.set(cv::CAP_PROP_FPS, 30);
	// auto i = camera.get(cv::CAP_PROP_EXPOSURE);
	// std::cout << "设置之前曝光为：" << i << std::endl;

	camera.set(cv::CAP_PROP_AUTO_EXPOSURE, 1);//1为手动曝光
    camera.set(cv::CAP_PROP_EXPOSURE, 5000);//值域1-5000

	// i = camera.get(cv::CAP_PROP_EXPOSURE);
	// std::cout << "现在曝光为：" << i << std::endl;
}

void Camera::run() {
    if(need_show_data)
    {
        if (!Is_capture_photo) {
            camera >> frame; // 捕获图像
            if (!frame.empty()) {
                cv::imshow("Camera Feed", frame);
                cv::waitKey(1); // 等待1毫秒以更新窗口
                }
        }
    }
}

void Camera::cleanup() {
    camera.release();
}

void Camera::captureAndSaveImage(const std::string& baseFilePath) {
    Is_capture_photo = true;
    if(!need_show_data)
    {
        camera >> frame;
    }
    std::string filePath = baseFilePath;
    int counter = 1;
    while (std::filesystem::exists(filePath)) {
        filePath = baseFilePath + std::to_string(counter++) + ".jpg"; // Generate new filename
    }

    if (!cv::imwrite(filePath, frame)) {
        throw std::runtime_error("Error: Could not save image!");
    }
    Is_capture_photo = false;
}

void Camera::captureAndSaveImage_fullPath(const std::string& filePath) {
    Is_capture_photo = true;
    if(!need_show_data)
    {
        camera >> frame;
    }
    cv::imwrite(filePath, frame);
    Is_capture_photo = false;
}
