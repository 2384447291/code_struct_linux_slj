#ifndef DMMOTOR_HPP
#define DMMOTOR_HPP

#include "Motor.hpp"
#include "DM_USB2CAN.hpp"

enum MotorMode {
    RELAX_MODE,
    MIT_MODE,
    POS_VEC_MODE,
    VEC_MODE
};

enum DMMode {
    MIT,
    POS_VEC,
    VEC
};

// 电机上限参数
const float P_MIN = -150.0f; //6.28*23=144.44rad;
const float P_MAX = 150.0f;  
const float V_MIN = -20.0f;  //20rad/s
const float V_MAX = 20.0f;
const float KP_MIN = 0.0f;
const float KP_MAX = 500.0f;
const float KD_MIN = 0.0f;
const float KD_MAX = 5.0f;
const float T_MIN = -3.0f;
const float T_MAX = 3.0f;

uint16_t float_to_uint(float x, float x_min, float x_max, int bits) {
    float span = x_max - x_min;
    float offset = x_min;
    return static_cast<uint16_t>((x - offset) * ((1 << bits) - 1) / span);
}
float uint_to_float(uint16_t x_int, float x_min, float x_max, int bits) {
    float span = x_max - x_min;
    float offset = x_min;
    return static_cast<float>(x_int) * span / ((1 << bits) - 1) + offset;
}
template <typename T>
void LIMIT_MIN_MAX(T &x, T min, T max) {
    if (x <= min) {
        x = min;
    } else if (x > max) {
        x = max;
    }
}

class DMmotor : public Motor
{
public:
    DM_USB2CAN* m_msg_center; 
    MotorMode m_MotorMode;
    DMMode m_DMMotorMode;
    uint32_t id_mask;
    uint32_t id;
    float feedback_pos;
    float feedback_vel;
    float feedback_torque;

    float control_p_des;
    float control_v_des;
    float control_k_p;
    float control_k_d;
    float control_torque;
    
    uint8_t m_recieve_msg[8];
    copy_solver m_solver;
        
    DMmotor(std::string _name):
        Motor(_name),
        feedback_pos(0.0), 
        feedback_vel(0.0), 
        feedback_torque(0.0), 
        control_p_des(0.0), 
        control_v_des(0.0),
        control_k_p(0.0), 
        control_k_d(0.0), 
        control_torque(0.0),
        m_solver(&m_recieve_msg[0],8)
        {}
    
    void Connectmotor(uint8_t ID, MotorMode _Motor_mode, DM_USB2CAN* _msg_center, DMMode _dm_mode)
    {
        id = ID, 
        m_MotorMode = _Motor_mode; 
        m_msg_center = _msg_center;
        m_DMMotorMode = _dm_mode;
        if(_dm_mode == DMMode::MIT)
        {
            id_mask = 0X00;
        }
        else if(_dm_mode == DMMode::POS_VEC)
        {
            id_mask = 0x100;
        }
        else if(_dm_mode == DMMode::VEC)
        {
            id_mask = 0x200;
        }
        m_msg_center->Solver_hashmap[id] = &m_solver;
        enable_motor();
        save_zero();
    }

    void enable_motor()
    {
        DM_USB2CAN_Send_Msg send_msg;
        send_msg.content_ptr->can_id = id + id_mask;
        uint8_t temp_data[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc};
        memcpy(send_msg.content_ptr->data,&temp_data,8);     
        m_msg_center->Others_enquene_send(send_msg); 
    }

    void disable_motor()
    {
        DM_USB2CAN_Send_Msg send_msg;
        send_msg.content_ptr->can_id = id + id_mask;
        uint8_t temp_data[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfd};
        memcpy(send_msg.content_ptr->data,&temp_data,8);     
        m_msg_center->Others_enquene_send(send_msg); 
    }

    void save_zero()
    {
        DM_USB2CAN_Send_Msg send_msg;
        send_msg.content_ptr->can_id = id + id_mask;
        uint8_t temp_data[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe};
        memcpy(send_msg.content_ptr->data,&temp_data,8);     
        m_msg_center->Others_enquene_send(send_msg); 
    }

    void motorcontrol(float _v_des , float _p_des = 0, float _kp = 0, float _kd = 0, float _tff = 0) 
    {
        if(m_DMMotorMode == DMMode::MIT)
        {
            LIMIT_MIN_MAX(_p_des, P_MIN, P_MAX);
            LIMIT_MIN_MAX(_v_des, V_MIN, V_MAX);
            LIMIT_MIN_MAX(_kp, KP_MIN, KP_MAX);
            LIMIT_MIN_MAX(_kd, KD_MIN, KD_MAX);
            LIMIT_MIN_MAX(_tff, T_MIN, T_MAX);

            uint16_t p = float_to_uint(_p_des, P_MIN, P_MAX, 16);
            uint16_t v = float_to_uint(_v_des, V_MIN, V_MAX, 12);
            uint16_t kp = float_to_uint(_kp, KP_MIN, KP_MAX, 12);
            uint16_t kd = float_to_uint(_kd, KD_MIN, KD_MAX, 12);
            uint16_t t = float_to_uint(_tff, T_MIN, T_MAX, 12);

            uint8_t temp_data[8] ={static_cast<uint8_t>(p >> 8), static_cast<uint8_t>(p & 0xFF),
                                    static_cast<uint8_t>(v >> 4), static_cast<uint8_t>(((v & 0xF) << 4) | (kp >> 8)),
                                    static_cast<uint8_t>(kp & 0xFF), static_cast<uint8_t>(kd >> 4),
                                    static_cast<uint8_t>(((kd & 0xF) << 4) | (t >> 8)), static_cast<uint8_t>(t & 0xFF)};

            DM_USB2CAN_Send_Msg send_msg;
            send_msg.content_ptr->can_id = id + id_mask;
            memcpy(send_msg.content_ptr->data,&temp_data,8);     
            m_msg_center->Others_enquene_send(send_msg);   
        }
        else if(m_DMMotorMode == DMMode::POS_VEC)
        {
            LIMIT_MIN_MAX(_p_des, P_MIN, P_MAX);
            LIMIT_MIN_MAX(_v_des, V_MIN, V_MAX);

            uint8_t* p = (uint8_t*)&(_p_des);
            uint8_t* v = (uint8_t*)&(_v_des);
                                    
            uint8_t temp_data[8] ={*p,*(p+1),*(p+2),*(p+3),*v,*(v+1),*(v+2),*(v+3)};
            DM_USB2CAN_Send_Msg send_msg;
            send_msg.content_ptr->can_id = id + id_mask;
            memcpy(send_msg.content_ptr->data,&temp_data,8);     
            m_msg_center->Others_enquene_send(send_msg);
        }
        else if(m_DMMotorMode == DMMode::VEC)
        {
            LIMIT_MIN_MAX(_v_des, V_MIN, V_MAX);
            uint8_t* v = (uint8_t*)&(_v_des);               
            uint8_t temp_data[8] ={*v,*(v+1),*(v+2),*(v+3),0x00,0x00,0x00,0x00};
            DM_USB2CAN_Send_Msg send_msg;
            send_msg.content_ptr->can_id = id + id_mask;
            send_msg.content_ptr->data_length = 0x04;
            memcpy(send_msg.content_ptr->data,&temp_data,8);     
            m_msg_center->Others_enquene_send(send_msg);
        }
    }

    void control()
    {
        if(m_MotorMode == MotorMode::RELAX_MODE)
        {
            motorcontrol(0.0, 0.0, 0.0, 0.0, 0.0);
        }
        else if(m_MotorMode == MotorMode::MIT_MODE)
        {
            if(m_DMMotorMode == DMMode::MIT)
            {
                motorcontrol(control_v_des, control_p_des, control_k_p, control_k_d, control_torque);
            }
            else
            {
                fprintf(stderr, "Motor Mode is %d Please set DMMode to MIT\n", m_DMMotorMode);
            }
        }
        else if(m_MotorMode == MotorMode::POS_VEC_MODE)
        {
            control_v_des = ((control_p_des - feedback_pos)*control_v_des) > 0 ? control_v_des : -control_v_des;

            if(m_DMMotorMode == DMMode::MIT)
            {
                if(abs(feedback_pos - control_p_des) < 1.0)
                {
                    motorcontrol(0.0f, control_p_des, control_k_p, control_k_d, 0.0f);
                }
                else
                {
                    motorcontrol(control_v_des, 0.0f, 0.0f, control_k_d, 0.0f);
                }
            }
            else if(m_DMMotorMode == DMMode::POS_VEC)
            {
                motorcontrol(control_v_des);
            }
            else
            {
                fprintf(stderr, "Motor Mode is %d Please set DMMode to MIT or POS_VEC\n", m_DMMotorMode);
            }
        }
        else if(m_MotorMode == MotorMode::VEC_MODE)
        {
            if(m_DMMotorMode == DMMode::MIT)
            {
                motorcontrol(control_v_des, 0.0f, 0.0f, control_k_d, 0.0f);
            }
            else if(m_DMMotorMode == DMMode::VEC)
            {
                motorcontrol(control_v_des);
            }
            else
            {
                fprintf(stderr, "Motor Mode is %d Please set DMMode to MIT or VEC\n", m_DMMotorMode);
            }
        }
    }

    void fdb_update()
    {
        uint8_t msg_copy[8];
        m_msg_center->getSolver(id,msg_copy);
        uint16_t packet_pos = static_cast<uint16_t>(msg_copy[1] << 8) | msg_copy[2];
        uint16_t packet_vec = static_cast<uint16_t>(msg_copy[3] << 4) | (msg_copy[4] >> 4);
        uint16_t packet_torque = static_cast<uint16_t>((msg_copy[4] & 0xF) << 8) | msg_copy[5];

        feedback_pos = uint_to_float(packet_pos, P_MIN, P_MAX, 16);
        feedback_vel = uint_to_float(packet_vec, V_MIN, V_MAX, 12);
        feedback_torque = uint_to_float(packet_torque, T_MIN, T_MAX, 12);
    }
};


#endif