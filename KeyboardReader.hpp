#ifndef KEYBOARDREADER_HPP
#define KEYBOARDREADER_HPP
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include "libevdev-1.0/libevdev/libevdev.h"
#include <unordered_map>
#include <string>

class KeyboardReader {
public:
    KeyboardReader(const std::string& devicePath);
    ~KeyboardReader();
    bool initialize();
    void readEvents();
    void down_event(std::string _key);
    void up_event(std::string _key);
    std::string getKeyName(int keyCode);
    int getKeyCode(std::string keyName);
    bool isKeyPressed(int keyCode);  // 新增方法来检查键状态

private:
    int fd;
    struct libevdev *dev;
    std::string devicePath;
    std::unordered_map<int, std::string> keyMap;
    std::unordered_map<int, bool> keyState;  // 用于跟踪每个键的状态
    void initializeKeyMap();
};

KeyboardReader::KeyboardReader(const std::string& devicePath)
    : fd(-1), dev(nullptr), devicePath(devicePath) {
    initializeKeyMap();
}

KeyboardReader::~KeyboardReader() {
    if (dev) {
        libevdev_free(dev);
    }
    if (fd >= 0) {
        close(fd);
    }
}

bool KeyboardReader::initialize() {
    fd = open(devicePath.c_str(), O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        std::cerr << "无法打开设备文件 " << devicePath << std::endl;
        return false;
    }
    int rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
        std::cerr << "无法初始化libevdev" << std::endl;
        return false;
    }
    std::cout << "设备名称: " << libevdev_get_name(dev) << std::endl;
    std::cout << "设备路径: " << devicePath << std::endl;
    return true;
}

void KeyboardReader::readEvents() {
    struct input_event ev;
    int rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL | LIBEVDEV_READ_FLAG_BLOCKING, &ev);
    if (rc == 0 && ev.type == EV_KEY) {
        if (ev.value == 1) { // 按键按下
            std::cout << "按键: " << getKeyName(ev.code) << " 被按下" << std::endl;
            keyState[ev.code] = true; // 更新状态为按下
            down_event(getKeyName(ev.code));
        } else if (ev.value == 0) { // 按键释放
            std::cout << "按键: " << getKeyName(ev.code) << " 被释放" << std::endl;
            keyState[ev.code] = false; // 更新状态为释放
            up_event(getKeyName(ev.code));
        }
    } else if (rc == -EAGAIN) {
        // usleep(1000); // 休眠1毫秒，避免CPU占用过高
    } else if (rc < 0) {
        // std::cerr << "读取事件失败 (" << strerror(-rc) << ")" << std::endl;
        // break;
    }
}

void KeyboardReader::up_event(std::string _key) {
    // 实现按键释放时的逻辑
}

void KeyboardReader::down_event(std::string _key) {
    // 其他按键事件处理
}

void KeyboardReader::initializeKeyMap() {
    keyMap = {
        // 初始化按键映射
        { KEY_ESC, "ESC" },
        { KEY_1, "1" },
        { KEY_2, "2" },
        { KEY_3, "3" },
        { KEY_4, "4" },
        { KEY_5, "5" },
        { KEY_6, "6" },
        { KEY_7, "7" },
        { KEY_8, "8" },
        { KEY_9, "9" },
        { KEY_0, "0" },
        { KEY_MINUS, "-" },
        { KEY_EQUAL, "=" },
        { KEY_BACKSPACE, "BACKSPACE" },
        { KEY_TAB, "TAB" },
        { KEY_Q, "Q" },
        { KEY_W, "W" },
        { KEY_E, "E" },
        { KEY_R, "R" },
        { KEY_T, "T" },
        { KEY_Y, "Y" },
        { KEY_U, "U" },
        { KEY_I, "I" },
        { KEY_O, "O" },
        { KEY_P, "P" },
        { KEY_LEFTBRACE, "[" },
        { KEY_RIGHTBRACE, "]" },
        { KEY_ENTER, "ENTER" },
        { KEY_LEFTCTRL, "LEFT CTRL" },
        { KEY_A, "A" },
        { KEY_S, "S" },
        { KEY_D, "D" },
        { KEY_F, "F" },
        { KEY_G, "G" },
        { KEY_H, "H" },
        { KEY_J, "J" },
        { KEY_K, "K" },
        { KEY_L, "L" },
        { KEY_SEMICOLON, ";" },
        { KEY_APOSTROPHE, "'" },
        { KEY_GRAVE, "" },
        { KEY_LEFTSHIFT, "LEFT SHIFT" },
        { KEY_BACKSLASH, "\\" },
        { KEY_Z, "Z" },
        { KEY_X, "X" },
        { KEY_C, "C" },
        { KEY_V, "V" },
        { KEY_B, "B" },
        { KEY_N, "N" },
        { KEY_M, "M" },
        { KEY_COMMA, "," },
        { KEY_DOT, "." },
        { KEY_SLASH, "/" },
        { KEY_RIGHTSHIFT, "RIGHT SHIFT" },
        { KEY_KPASTERISK, "NUMPAD *" },
        { KEY_LEFTALT, "LEFT ALT" },
        { KEY_SPACE, "SPACE" },
        { KEY_CAPSLOCK, "CAPS LOCK" },
        { KEY_F1, "F1" },
        { KEY_F2, "F2" },
        { KEY_F3, "F3" },
        { KEY_F4, "F4" },
        { KEY_F5, "F5" },
        { KEY_F6, "F6" },
        { KEY_F7, "F7" },
        { KEY_F8, "F8" },
        { KEY_F9, "F9" },
        { KEY_F10, "F10" },
        { KEY_NUMLOCK, "NUM LOCK" },
        { KEY_SCROLLLOCK, "SCROLL LOCK" },
        { KEY_KP7, "NUMPAD 7" },
        { KEY_KP8, "NUMPAD 8" },
        { KEY_KP9, "NUMPAD 9" },
        { KEY_KPMINUS, "NUMPAD -" },
        { KEY_KP4, "NUMPAD 4" },
        { KEY_KP5, "NUMPAD 5" },
        { KEY_KP6, "NUMPAD 6" },
        { KEY_KPPLUS, "NUMPAD +" },
        { KEY_KP1, "NUMPAD 1" },
        { KEY_KP2, "NUMPAD 2" },
        { KEY_KP3, "NUMPAD 3" },
        { KEY_KP0, "NUMPAD 0" },
        { KEY_KPDOT, "NUMPAD ." },
        { KEY_F11, "F11" },
        { KEY_F12, "F12" }
        // 添加其他按键映射
    };

    for (const auto& key : keyMap) {
        keyState[key.first] = false;
    }
}

std::string KeyboardReader::getKeyName(int keyCode) {
    if (keyMap.find(keyCode) != keyMap.end()) {
        return keyMap[keyCode];
    }
    return "UNKNOWN";
}

int KeyboardReader::getKeyCode(std::string keyName) {
    for (const auto& pair : keyMap) {
        if (pair.second == keyName) {
            return pair.first;
        }
    }
    return -1;
}

bool KeyboardReader::isKeyPressed(int keyCode) {
    // 返回键的当前状态，是否按下
    if (keyState.find(keyCode) != keyState.end()) {
        return keyState[keyCode];
    }
    return false;
}

#endif
