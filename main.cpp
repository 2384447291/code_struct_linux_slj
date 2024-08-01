#include "Timer.h"
#include "IrisTac.hpp"
#include "KeyboardReader.hpp"

int main()
{
    Gloabl_Timer::Instance();
    PeriodicTaskManager::Instance();

    DM_USB2CAN test = DM_USB2CAN("DM_USB2CAN1",100,0.001,921600,"/dev/ttyACM0",128,1024,8);
    test.start();
    IrisTac m_iristac;
    m_iristac.start();

    KeyboardReader reader("/dev/input/event20"); // 替换为你的键盘设备文件路径
    reader.initialize();
    // RobotRunner::Instance()->Print_Controller();
    // RobotRunner::Instance()->Print_RobotPart();
    // RobotRunner::Instance()->Print_Module();

    int64_t lastTimeMs = 0; 
    while(1)
    {
        reader.readEvents();
        if(reader.isKeyPressed(reader.getKeyCode("LEFT SHIFT")))
        {
            m_iristac.m_DisplacementStageController.m_OrbitMotor[z].m_MotorMode = MotorMode::MIT_MODE;
            m_iristac.m_DisplacementStageController.m_OrbitMotor[z].control_v_des = 0.0f;
            if(m_iristac.m_DisplacementStageController.m_Is_motor_init[z])
            {
                m_iristac.m_DisplacementStageController.m_position_set[z] += 0.00001f;
            }
        }
        else if(reader.isKeyPressed(reader.getKeyCode("LEFT CTRL")))
        {
            m_iristac.m_DisplacementStageController.m_OrbitMotor[z].m_MotorMode = MotorMode::MIT_MODE;
            m_iristac.m_DisplacementStageController.m_OrbitMotor[z].control_v_des = 0.0f;
            if(m_iristac.m_DisplacementStageController.m_Is_motor_init[z])
            {
                m_iristac.m_DisplacementStageController.m_position_set[z] -= 0.00001f;     
            }     
        }
        if (Gloabl_Timer::hasElapsedMs(1000, lastTimeMs))
        {
        }
    }
}