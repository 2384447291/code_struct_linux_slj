#include "DM_USB2CAN.hpp"
#include "Timer.h"
#include "string.h"

int64_t time_sample_DM_USB2CAN = 0; 

void DM_USB2CAN::run()
{
    //收包并发包
    UartCom::run();
    //收包处理

    if (Gloabl_Timer::hasElapsedMs(1000, time_sample_DM_USB2CAN))
    {
        if(m_packet_send_allS > 4100)
        {
            std::cout << std::dec << get_name() << " over send_rate " << m_packet_send_allS << std::endl;            
        }
        m_packet_recieve_allS = m_packet_recieve_all;
        m_packet_recieve_all = 0;
        // std::cout << std::dec << "recieve_rate " << m_packet_recieve_allS<< std::endl;

        m_packet_send_error_allS = m_packet_send_error_all;
        m_packet_send_error_all = 0;
        // std::cout << std::dec << "send_error_rate " << m_packet_send_error_allS<< std::endl;
    }  

    while(!m_recieve_buffer.isEmpty())
    {
        uint8_t _data = m_recieve_buffer.dequeue();
        recieve_buffer.push_back(_data);

        if (recieve_buffer.size() == 1) {
            if (recieve_buffer[0] != 0xAA) {
                recieve_buffer.erase(recieve_buffer.begin());
                continue;
            } 
        }
        else if(recieve_buffer.size() == 2)
        {
            //0x01接收失败 0x11接收成功 0x02发送失败 0x12发送成功,只有两种消息需要处理
            if(recieve_buffer[1]!=0x11 && recieve_buffer[1]!=0x02)
            {
                recieve_buffer.clear();
            }
        }
        else if(recieve_buffer.size() == 16)
        {
            // for (const auto& byte : recieve_buffer) {
            //     std::cout << std::hex << static_cast<int>(byte) << " ";
            // }
            // std::cout << std::endl;
            if(recieve_buffer[15] == 0x55)
            {
                temp_can_msg.can_id = (uint32_t)recieve_buffer[3] | (uint32_t)recieve_buffer[4] << 8 | (uint32_t)recieve_buffer[5] << 16 | (uint32_t)recieve_buffer[6] << 24; 
                //接收成功处理数据
                if(recieve_buffer[1] == 0x11)
                {
                    if(!connect_lock)
                    {
                        connect_lock = true;
                    }
                    //所有damiao电机的反馈帧0x00，要做特殊处理
                    if(temp_can_msg.can_id == 0)
                    {
                        temp_can_msg.can_id |= (recieve_buffer[7]&0x0F);
                    }

                    // for (const auto& byte : recieve_buffer) {
                    //     std::cout << std::hex << static_cast<int>(byte) << " ";
                    // }
                    // std::cout << std::endl;
                    m_packet_recieve_all++;
                    if (Solver_hashmap.find(temp_can_msg.can_id) != Solver_hashmap.end()) {
                        copy_solver* temp_solver = Solver_hashmap[temp_can_msg.can_id];
                        std::unique_lock<std::shared_mutex> recieve_lock(recieve_quene_mutex);
                        memcpy(temp_solver->target_adrr,&recieve_buffer[7],temp_solver->copy_num);
                        recieve_lock.unlock();
                        temp_solver->m_update_rate++;
                    } else {
                        fprintf(stderr,"canid: %d not found\n",temp_can_msg.can_id);
                    }       
                }
                else
                {
                    m_packet_send_error_all++;
                    //发送失败再次发送
                    if(connect_lock)
                    {
                        DM_USB2CAN_Send_Msg resend_msg;
                        resend_msg.content_ptr->can_id = temp_can_msg.can_id;
                        memcpy(resend_msg.content_ptr->data,&recieve_buffer[7],8);     
                        m_send_buffer.enqueueFront(resend_msg);
                    }
                }
            }
            recieve_buffer.clear();
        }
    }
}