#ifndef DISPLACEMENTSTAGECONTROLLER_HPP
#define DISPLACEMENTSTAGECONTROLLER_HPP

#include "RobotRunner.hpp"
#include "DMmotor.hpp"
#include "Timer.h"
#include "Math_Tool.hpp"

#define Z_MAX 150
#define Z_MIN 0

//右手坐标系
enum orbit_type{
    x = 0,
    y,
    z,
    orbit_length
};
enum init_state{
    set,
    waiting,
    zero,
    reset,
};
class DisplacementStageController : public RobotController
{
    public:
        DMmotor m_OrbitMotor[3];
        float m_position_set[3];
        bool m_Is_motor_init[3] = {false, false, false};
        init_state m_init_state[3] = {set,set,set};
        double stuck_time[3] = {0, 0, 0};

        Module<DisplacementStageController> m_update_module;

        DisplacementStageController():RobotController("DisplacementStageController"),
        m_OrbitMotor{DMmotor("x_motor"),DMmotor("y_motor"),DMmotor("z_motor")},
        m_update_module{MT_CONTROLLER,this,&DisplacementStageController::update,"DisplacementStageController_update_module"}
        {};

        void init() override{
            DM_USB2CAN* massage_ptr = dynamic_cast<DM_USB2CAN*> (PeriodicTaskManager::Instance()->FindTask("DM_USB2CAN1"));
            if(massage_ptr == nullptr)
            {
                fprintf(stderr,"can not find communication interface\n");
                return;
            }
            for(int i = 0; i < orbit_length; i++)
            {
                m_OrbitMotor[i].Connectmotor(i+1,MotorMode::RELAX_MODE,massage_ptr,DMMode::MIT);
                m_OrbitMotor[i].control_k_d = 1.0f;
                m_OrbitMotor[i].control_k_p = 10.0f;
            }
        };

    void update()
    {
        // if(m_Is_motor_init[x]&&m_Is_motor_init[y]&&m_Is_motor_init[z])
        if(m_Is_motor_init[z])
        {
            // m_OrbitMotor[z].m_MotorMode = MotorMode::MIT_MODE;
            m_position_set[z] = clamp(m_position_set[z],(float)Z_MIN,(float)Z_MAX);
            m_OrbitMotor[z].control_p_des =-m_position_set[z];
        }
        else
        {
            update_init_state();
        }
    }

    void update_init_state()
    {
        for(int i = 0; i < orbit_length; i++)
        {
            if(!m_Is_motor_init[i])
            {
                if(m_init_state[i] == set)
                {
                    m_OrbitMotor[i].m_MotorMode = MotorMode::MIT_MODE;
                    m_OrbitMotor[i].control_p_des = 0;
                    m_OrbitMotor[i].control_v_des = 0;
                    m_OrbitMotor[i].control_k_p = 0;
                    m_OrbitMotor[i].control_k_d = 0;
                    m_OrbitMotor[i].control_torque = 0.12;
                    m_init_state[i] = waiting;
                }
                else if(m_init_state[i] == waiting)
                {
                    if(abs(m_OrbitMotor[i].feedback_vel)>0.1)
                    {
                        stuck_time[i] = Gloabl_Timer::Instance()->getSeconds();
                    }
                    if(Gloabl_Timer::Instance()->getSeconds() - stuck_time[i] > 0.15)
                    {
                        m_init_state[i] = zero;
                    }
                }
                else if(m_init_state[i] == zero)
                {
                    m_OrbitMotor[i].save_zero();
                    if(abs(m_OrbitMotor[i].feedback_pos) <0.01)
                    {
                        m_init_state[i] = reset;
                    }
                }
                else if (m_init_state[i] == reset)
                {
                    m_OrbitMotor[i].m_MotorMode = MotorMode::POS_VEC_MODE;
                    m_OrbitMotor[i].control_k_d = 1.0f;
                    m_OrbitMotor[i].control_k_p = 10.0f;
                    m_OrbitMotor[i].control_p_des = -20.0f;
                    m_OrbitMotor[i].control_v_des = 20.0f;
                    m_OrbitMotor[i].control_torque = 0.0;
                    m_position_set[i] = 20.0f;
                    if(abs(m_OrbitMotor[i].feedback_pos-m_OrbitMotor[i].control_p_des)<0.05f) 
                    {
                        m_Is_motor_init[i] = true;
                    } 
                }
            }
        }
    }
};
#endif