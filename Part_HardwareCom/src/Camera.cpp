#include "Camera.hpp"
#include <filesystem>

void Camera::init() {
    camera.open(0);
    if (!camera.isOpened()) {
        throw std::runtime_error("Error: Camera not opened!");
    }
    camera.set(cv::CAP_PROP_FPS, 30);
    camera.set(cv::CAP_PROP_AUTO_EXPOSURE, 0.25);
    camera.set(cv::CAP_PROP_EXPOSURE, -6);
}

void Camera::run() {
    cv::Mat frame;
    camera >> frame; // 捕获图像
    if (frame.empty()) {
        throw std::runtime_error("Error: Frame is empty!");
    }
    cv::imshow("Camera Feed", frame);
    cv::waitKey(1); // 等待1毫秒以更新窗口
}

void Camera::cleanup() {
    camera.release();
}

void Camera::captureAndSaveImage(const std::string& baseFilePath) {
    Is_capture_photo = true;
    cv::Mat frame;
    camera >> frame; // Capture image
    if (frame.empty()) {
        throw std::runtime_error("Error: Frame is empty!");
    }

    std::string filePath = baseFilePath;
    int counter = 1;
    while (std::filesystem::exists(filePath)) {
        filePath = baseFilePath + "_" + std::to_string(counter++) + ".jpg"; // Generate new filename
    }

    if (!cv::imwrite(filePath, frame)) {
        throw std::runtime_error("Error: Could not save image!");
    }
    Is_capture_photo = false;
}