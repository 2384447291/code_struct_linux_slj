#include "Timer.h"
#include "Camera.hpp"
#include "IrisTac_Project.hpp"
#include "KeyboardReader.hpp"
#include <stdio.h>
#include "Math_Tool.hpp"

#include <QtWidgets/QApplication>
#include "mainwindow.h"
 
#define NEED_PLOT 0
#define MAX_Y -15
#define MIN_Y -25
#define CHANNEL_NUM 3

#if NEED_PLOT
    
    CurvePlotFifo* fifo = nullptr;
    void Plotfunc(int argc, char *argv[])
    {
        QApplication a(argc, argv);
        MainWindow w(MIN_Y,MAX_Y,CHANNEL_NUM);
        fifo = w.GetFIFO();
        w.show();
        a.exec();
    }
#endif

int main(int argc, char *argv[])
{
    Gloabl_Timer::Instance();
    PeriodicTaskManager::Instance();

    // DM_USB2CAN test = DM_USB2CAN("DM_USB2CAN1",100,0.001,921600,"/dev/ttyACM0",128,1024,8);
    // test.start();

    IrisTac_Project Project;
    Project.start();

    #if NEED_PLOT
    std::thread t(Plotfunc,argc,argv);
    #endif

    Camera camera = Camera(true,"USB_Camera",100,0.01);
    camera.start();

    KeyboardReader reader;
    reader.initialize();

    // RobotRunner::Instance()->Print_Controller();
    // RobotRunner::Instance()->Print_RobotPart();
    // RobotRunner::Instance()->Print_Module();

    int64_t lastTimeMs = 0; 
    int64_t lastTimeMs2 = 0; 
    int64_t lastTimeMs3 = 0; 
    int64_t lastTimeMs4 = 0; 
    bool Is_changing_LED = true;
    int photo_num = 0;

    Project.m_IrisTacController.m_IrisTac.Single_light(3,2,255);
    while(1)
    {
        reader.readEvents();

        #if NEED_PLOT
        if (Gloabl_Timer::hasElapsedMs(10, lastTimeMs2))
        {
            if(fifo!=nullptr)
            {
                QVector<double> newData;
                double key = QTime::currentTime().msecsSinceStartOfDay() / 1000.0;
                newData.append(key);
                newData.append(-Project.m_DisplacementStageController.Pos_filter[x].previousFilteredValue);
                newData.append(Project.m_DisplacementStageController.m_OrbitMotor[x].control_p_des);
                newData.append(Project.m_DisplacementStageController.m_OrbitMotor[x].feedback_pos);
                if (!fifo->isFull())
                {
                    fifo->write(newData);
                }            
            }
        }
        #endif
        if (Gloabl_Timer::hasElapsedMs(100, lastTimeMs))
        {
            // if(reader.isKeyPressed(reader.getKeyCode("LEFT SHIFT")))
            // {
            //     if(Project.m_DisplacementStageController.m_Is_motor_init[x])
            //     {
            //         Project.m_DisplacementStageController.m_position_set[x] += 1.5f;
            //     }
            // }
            // else if(reader.isKeyPressed(reader.getKeyCode("LEFT CTRL")))
            // {
            //     if(Project.m_DisplacementStageController.m_Is_motor_init[x])
            //     {
            //         Project.m_DisplacementStageController.m_position_set[x] -= 1.5f;     
            //     }     
            // }
            // fprintf(stderr, "control_pos: %f\n", Project.m_DisplacementStageController.m_OrbitMotor[x].control_p_des);
            // fprintf(stderr, "feed_pos: %f\n", Project.m_DisplacementStageController.m_OrbitMotor[x].feedback_pos);
            // fprintf(stderr, "i_torque_vel: %f\n", Project.m_DisplacementStageController.m_OrbitMotor[x].control_i_torque);

            if(reader.isKeyPressed(reader.getKeyCode("LEFT CTRL")))
            {
                float brightness_ration = Project.m_IrisTacController.m_IrisTac.Get_bright_ratio();
                brightness_ration = clamp(brightness_ration - 0.03f, 0.0f, 1.0f);
                std::cout << brightness_ration << std::endl;
                Project.m_IrisTacController.m_IrisTac.Set_color_bright(brightness_ration);
            }
            else if(reader.isKeyPressed(reader.getKeyCode("LEFT SHIFT")))
            {
                float brightness_ration = Project.m_IrisTacController.m_IrisTac.Get_bright_ratio();
                brightness_ration = clamp(brightness_ration + 0.03f, 0.0f, 1.0f);
                std::cout << brightness_ration << std::endl;
                Project.m_IrisTacController.m_IrisTac.Set_color_bright(brightness_ration);
            }
            else if(reader.isKeyPressed(reader.getKeyCode("SPACE")))
            {
                camera.captureAndSaveImage("../Capture_Photo/");
            }
        }

        // if (Gloabl_Timer::hasElapsedMs(200, lastTimeMs3))
        // {
        //     if(photo_num < 256*24)
        //     {
        //         if(Is_changing_LED){
        //             uint8_t light_id = photo_num/256;
        //             uint8_t bright = photo_num % 256;
        //             Project.m_IrisTacController.m_IrisTac.Single_light(light_id,2,bright);
        //         }
        //         else{
        //             int light_id = photo_num/256;
        //             std::string S_light_id = formatNumber(light_id, 2);
        //             int bright = photo_num % 256;
        //             std::string S_bright = formatNumber(bright, 3);
        //             std::string filePath = "../Capture_Photo/xx_xxx_2/" +  S_light_id + "_" + S_bright + "_2" +  ".jpg"; // Generate new filename
        //             camera.captureAndSaveImage_fullPath(filePath);
        //             filePath = S_light_id + "_" + S_bright + "_0" +  ".jpg"; // Generate new filename
        //             fprintf(stderr, "photo_num is: %d", photo_num);
        //             fprintf(stderr, " address is: %s\n", filePath.c_str());
        //             photo_num++;
        //         }
        //         Is_changing_LED = !Is_changing_LED;
        //     }
        // }
    }
}
