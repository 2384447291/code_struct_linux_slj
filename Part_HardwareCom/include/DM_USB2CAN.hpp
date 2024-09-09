#ifndef DM_USB2CAN_HPP
#define DM_USB2CAN_HPP
#include "UartCommunication.hpp"
#include <unordered_map>
#include <cstring>

#pragma pack(push, 1) // Ensure no padding between struct members
struct DM_USB2CAN_Message {
    uint8_t header[2];             // Frame header
    uint8_t frame_length_command[2];// Frame length + command
    uint32_t send_count;           // Send count (little-endian)
    uint32_t time_interval;        // Time interval (little-endian)
    uint8_t id_type;               // ID type
    uint32_t can_id;               // CAN_ID (little-endian)
    uint8_t frame_type;            // Frame type
    uint8_t data_length;           // Data length
    uint8_t idacc_dataacc[2];      // idacc + dataacc
    uint8_t data[8];               // 8 bytes of data
    uint8_t crc;                   // CRC checkMs
};
#pragma pack(pop)

class DM_USB2CAN_Send_Msg : public Msg {
public:
    DM_USB2CAN_Message* content_ptr;
    DM_USB2CAN_Send_Msg() {
        msg_content.resize(sizeof(DM_USB2CAN_Message));
        content_ptr = reinterpret_cast<decltype(content_ptr)>(msg_content.data());
        // Initialize content
        content_ptr->header[0] = 0x55;
        content_ptr->header[1] = 0xAA;
        content_ptr->frame_length_command[0] = 0x1e;
        content_ptr->frame_length_command[1] = 0x01;
        content_ptr->send_count = 1;
        content_ptr->time_interval = 10;
        content_ptr->id_type = 0x00;
        content_ptr->can_id = 0;
        content_ptr->frame_type = 0x00;
        content_ptr->data_length = 0x08;
        content_ptr->idacc_dataacc[0] = 0x00;
        content_ptr->idacc_dataacc[1] = 0x00;
        memset(content_ptr->data, 0, sizeof(content_ptr->data));
        content_ptr->crc = 0x88;
    }

    void printHexContent() const {
        // Print the content in hexadecimal format
        for (const auto& byte : msg_content) {
            std::cout << std::hex << static_cast<int>(byte) << " ";
        }
        std::cout << std::endl;
    }
};

struct can_msg
{
    uint8_t message[8];
    uint32_t can_id;
};

class DM_USB2CAN : public UartCom{
    public:
        //串口波特率为921600，1s能发送921600/(30*（8+1）)=3413个控制帧。
        //1s能接收921600/(16*（8+1）)=6400个反馈帧。
        //发送频率和接收频率是两个东西，波特率主要限制的是接收频率，发送可以很快，但由于波特率采样频率的限制，接收会出问题，收到的东西只有这么多
        //上位机最高的发送频率为16000，下位机采样过后因为没有应答以6200左右反馈接收错误。

        //实测虽然发送频率为3413，超负载到4000还算稳定，偶尔会丢几帧，考虑到can负载为4000则上限定为4000，

        //CAN波特率为1000000，1个can帧111字节，1个反馈帧，1个控制帧，1000000/（111*2）= 4504个控制流，
        //(实测为4000帧)，每个电机驱动会锁定反馈上限为4000hz来保证can总线负载率，多个电机连在一起也会保证最大控制频率在4000左右
        //优先保证id小的电机，id1电机6000控制，id2电机1000控制，最后结果为id1=3500hz,id2=500hz
        //若多者的和<4000,自然每一个电机都小于4000，则控制符合设定。
        DM_USB2CAN(std::string _name, uint8_t _prefer_cpu, float _update_rate, int _baudrate, const char *_pathname,uint32_t _send_buffer_size, uint32_t _recieve_buffer_size, uint8_t _every_time_send_max):
        UartCom(_name,_prefer_cpu,_update_rate,_baudrate,_pathname, _send_buffer_size, _recieve_buffer_size, _every_time_send_max){}
        
        //收包检测助手
        uint32_t m_packet_recieve_allS = 0;  
        uint32_t m_packet_recieve_all = 0;

        uint32_t m_packet_send_error_allS = 0;  
        uint32_t m_packet_send_error_all = 0;

        std::unordered_map<uint32_t, copy_solver*> Solver_hashmap;

        void getSolver(uint32_t id, uint8_t* feedback)
        {
            std::unique_lock<std::shared_mutex> recieve_lock(recieve_quene_mutex);
            memcpy(feedback,Solver_hashmap[id]->target_adrr,8);
        }
    
    private:
        //接收辅助变量
        uint8_t recieve_buffer_length;
        std::vector<uint8_t> recieve_buffer;
        can_msg temp_can_msg;
        bool connect_lock = false;
        
        void run() override;
};
#endif