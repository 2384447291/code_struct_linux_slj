#include "Timer.h"
#include "IrisTac.hpp"

int main()
{
    Gloabl_Timer::Instance();
    PeriodicTaskManager::Instance();

    DM_USB2CAN test = DM_USB2CAN("DM_USB2CAN1",100,0.001,921600,"/dev/ttyACM0",128,1024,8);
    test.start();
    IrisTac m_iristac;
    m_iristac.start();
    // RobotRunner::Instance()->Print_Controller();
    // RobotRunner::Instance()->Print_RobotPart();
    // RobotRunner::Instance()->Print_Module();
    int64_t lastTimeMs = 0; 
    while(1)
    {
        if (Gloabl_Timer::hasElapsedMs(50, lastTimeMs))
        {
            std::cout << std::dec << m_iristac.m_DisplacementStageController.m_OrbitMotor[2].feedback_pos<< " rad" << std::endl;
        }
    }
}