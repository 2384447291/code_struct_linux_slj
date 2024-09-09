// #include "dmmotor.hpp"
// #include "Timer.h"
// #include "RobotRunner.hpp"
// #include "DM_USB2CAN.hpp"

// class testController : RobotController
// {
//     public:
//         DMmotor test1;
//         DMmotor test2;
//         testController():
//         RobotController("testcontroller"),
//         test1("test1"),test2("test2"),
//         myModule(MT_CONTROLLER,this,&testController::run1,"myModule"){};

//     void init() override{
//         DM_USB2CAN* massage_ptr = dynamic_cast<DM_USB2CAN*> (PeriodicTaskManager::Instance()->FindTask("DM_USB2CAN1"));
//         if(massage_ptr == nullptr)
//         {
//             fprintf(stderr,"can not find communication interface\n");
//             return;
//         }
//         test1.Connectmotor(1,MotorMode::RELAX_MODE,massage_ptr,DMMode::MIT);
//         test2.Connectmotor(2,MotorMode::RELAX_MODE,massage_ptr,DMMode::MIT);
//         test1.control_k_d = 1.0f;
//         test1.control_k_p = 5.0f;
//         test2.control_k_d = 1.0f;
//         test2.control_k_p = 5.0f;
//     }

//     void run1()
//     {
//         // test1.control_v_des = -4.0f;
//         // test1.m_MotorMode = MotorMode::VEC_MODE;
//     }

//     Module<testController> myModule;
// };

// class Myrobot : public RobotRunner
// {
//     public:
//         Myrobot():RobotRunner(this){}
//         testController controller1;
// };

int main()
{
    // Gloabl_Timer::Instance();
    // PeriodicTaskManager::Instance();
    // DM_USB2CAN test = DM_USB2CAN("DM_USB2CAN1",100,0.001,921600,"/dev/ttyACM0",128,1024,8);
    // test.start();
    // Myrobot robot;
    // robot.start();
    // // RobotRunner::Instance()->Print_Controller();
    // // RobotRunner::Instance()->Print_RobotPart();
    // // RobotRunner::Instance()->Print_Module();
    // int64_t lastTimeMs = 0; 
    // while(1)
    // {
    //     if (Gloabl_Timer::hasElapsedMs(100, lastTimeMs))
    //     {
    //         std::cout << std::dec << robot.controller1.test1.feedback_pos<< " rad" << std::endl;
    //     }
    // }
}

