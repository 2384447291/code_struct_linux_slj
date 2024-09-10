#ifndef DISPLACEMENTSTAGECONTROLLER_HPP
#define DISPLACEMENTSTAGECONTROLLER_HPP

#include "RobotRunner.hpp"
#include "DMmotor.hpp"
#include "Timer.h"
#include "Math_Tool.hpp"

#define X_MAX 150
#define X_MIN 0

//右手坐标系
enum orbit_type{
    z = 0,
    x,
    y,
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
        LowPassFilter<double> Pos_filter[3];
        DMmotor m_OrbitMotor[3];
        float m_position_set[3];
        bool m_Is_motor_init[3] = {false, false, false};
        init_state m_init_state[3] = {set,set,set};
        double stuck_time[3] = {0, 0, 0};

        Module<DisplacementStageController> m_update_module;

        DisplacementStageController():RobotController("DisplacementStageController"),
        //x-2//y-3//z-1
        m_OrbitMotor{DMmotor("z_motor"),DMmotor("x_motor"),DMmotor("y_motor")},
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
        if(m_Is_motor_init[x])
        {
            m_position_set[x] = clamp(m_position_set[x],(float)X_MIN,(float)X_MAX);
            m_OrbitMotor[x].control_p_des = -Pos_filter[x].filter(m_position_set[x]);          
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
                    m_OrbitMotor[i].control_torque = 0.25;
                    m_init_state[i] = waiting;
                }
                else if(m_init_state[i] == waiting)
                {
                    if(abs(m_OrbitMotor[i].feedback_vel)>1.0)
                    {
                        stuck_time[i] = Gloabl_Timer::Instance()->getSeconds();
                    }
                    if(Gloabl_Timer::Instance()->getSeconds() - stuck_time[i] > 0.5)
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
                    m_position_set[i] = -m_OrbitMotor[i].control_p_des;
                    Pos_filter[i].previousFilteredValue = m_position_set[i];
                    Pos_filter[i].alpha = 0.01;
                    if(abs(m_OrbitMotor[i].feedback_pos-m_OrbitMotor[i].control_p_des)<0.05f) 
                    {
                        m_Is_motor_init[i] = true;
                        m_OrbitMotor[i].m_MotorMode = MotorMode::MIT_MODE;
                        m_OrbitMotor[i].control_v_des = 0.0f;
                        m_OrbitMotor[i].control_k_d = 1.0f;
                        m_OrbitMotor[i].control_k_p = 10.0f;
                    } 
                }
            }
        }
    }
};
#endif