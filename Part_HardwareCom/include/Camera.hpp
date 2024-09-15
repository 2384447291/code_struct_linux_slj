#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "PeriodicTask.hpp"
#include <opencv2/opencv.hpp>
#include <iomanip>
#include <shared_mutex>
#include <mutex>

class Camera : public PeriodicTask {
public:
    Camera(bool _need_show_data, std::string _name, uint8_t _prefer_cpu, float _update_rate)
    :need_show_data(_need_show_data),
    PeriodicTask(_update_rate, _name, _prefer_cpu, sched_get_priority_max(SCHED_FIFO), SCHED_FIFO) {}

    // 继承自 PeriodicTask 的函数
    void init() override;
    void run() override;
    void cleanup() override;

    void captureAndSaveImage(const std::string& filePath);

    void captureAndSaveImage_fullPath(const std::string& filePath);

private:
    cv::VideoCapture camera;
    bool Is_capture_photo;
    bool need_show_data;
    cv::Mat frame;
};

#endif
