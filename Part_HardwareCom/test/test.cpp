int main()
{
    // Gloabl_Timer::Instance();
    // PeriodicTaskManager testmanager;
    // DM_USB2CAN test("testinterface",100,0.001,921600,"/dev/ttyACM0",128,1024,8);

    // DMmotor testmotor(3,MotorMode::POS_VEC_MODE,&test,DMMode::MIT);
    // int64_t lastTimeMs = 0; 
    // int64_t lastTimeMs1 = 0; 
    // testmotor.control_v_des = -4.0f;
    // testmotor.control_k_d = 1.0f;
    // testmotor.control_p_des = 120.0f;
    // testmotor.control_k_p = 5.0f;
    // while(1)
    // {
    //     if (Gloabl_Timer::hasElapsedMs(1, lastTimeMs))
    //     {
    //         testmotor.resolve_feedback();
    //         testmotor.motor_move();
    //         // std::cout << std::dec << testmotor.feedback_vel<< " rad/s" << std::endl;
    //         // std::cout << std::dec << testmotor.feedback_pos<< " rad" << std::endl;
    //     }
    //     if (Gloabl_Timer::hasElapsedMs(1000, lastTimeMs1))
    //     {
    //         testmotor.m_solver.m_update_rateS = testmotor.m_solver.m_update_rate;
    //         testmotor.m_solver.m_update_rate = 0;
    //         // std::cout << std::dec << "testmotor recieve_rate " << testmotor.m_solver.m_update_rateS<< std::endl;
    //     }

    //     if(Gloabl_Timer::getMs() >= 2000)
    //     {
    //         testmotor.control_v_des = 4.0f;
    //         testmotor.control_p_des = 2.0f;
    //     }
    // }
}
