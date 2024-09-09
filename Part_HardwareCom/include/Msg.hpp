#ifndef MSG_HPP
#define MSG_HPP
#include <iostream>
#include <vector>
#include <iomanip>
class Msg {
public:
    Msg(){}
    std::vector<u_int8_t> msg_content;

    void printHex() {
    for (const auto& byte : msg_content) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl; // 恢复为十进制格式
}
};
#endif
