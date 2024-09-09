#ifndef IRISTAC_HPP
#define IRISTAC_HPP
#include "RobotRunner.hpp"
#include "Math_Tool.hpp"

const int LED_NUM = 24;
const int LED_REGIN = 8;
const int LED_DATA = 3;

enum LED_Pattern
{
    full_red = 0,
    split_three_color,
};

//这里是阉割版的串口不需要发，不需要收，所以不继承UARTCOM
class IrisTac : public Robot_part
{
    public:
        IrisTac(std::string _name, const char * _uartname):
        Robot_part(_name),
        IrisTac_LED_control(MT_ACTUATOR, this, &IrisTac::LED_control, _name + "LED_control"),
        IrisTac_Camera_control(MT_ACTUATOR, this, &IrisTac::Camera_control, _name + "Camera_control"),
        uartname(_uartname),
        baudrate(115200)
        {
            init_uart();
            m_led_pattern = LED_Pattern::full_red;
            // 设置 LED 颜色
            for (int i = 0; i < LED_REGIN; ++i) {
                LED_list[i][0] = 255; // Red
                LED_list[i][1] = 0;
                LED_list[i][2] = 0;
            }
            for (int i = LED_REGIN; i < 2 * LED_REGIN; ++i) {
                LED_list[i][0] = 0;
                LED_list[i][1] = 255; // Green
                LED_list[i][2] = 0;
            }
            for (int i = 2 * LED_REGIN; i < 3 * LED_REGIN; ++i) {
                LED_list[i][0] = 0;
                LED_list[i][1] = 0;
                LED_list[i][2] = 255; // Blue
            }
        }

        Module<IrisTac> IrisTac_LED_control;
        Module<IrisTac> IrisTac_Camera_control;

        //LED控制
        void LED_control();
        bool need_change_color = true;

        void ChangeColor() {
            uint8_t temp_LED_list[LED_NUM][LED_DATA] = {0};
            for(int i = 0; i < LED_NUM; ++i)
            {
                for(int j = 0; j < LED_DATA; ++j)
                {
                    temp_LED_list[i][j] = clamp(static_cast<uint8_t>((float)LED_list[i][j]*bright_ratio),static_cast<uint8_t>(0),static_cast<uint8_t>(255));
                }
            }
            for (int num = 0; num < LED_NUM; ++num) {
                uint8_t temp[] = {0xAA, 0xBB, static_cast<uint8_t>(num), temp_LED_list[num][0], temp_LED_list[num][1], temp_LED_list[num][2]};
                const char* char_data = reinterpret_cast<const char*>(temp);
                if(uart_write(fd, char_data, (sizeof(temp)/sizeof(temp[0])) ) <= 0)
                {
                    need_change_color = true;
                } 
            }
        }

        void Camera_control();
        //通讯通用接口
        void com_init();

        int uart_write(int fd,const char *w_buf,size_t len);
        ssize_t safe_write(int fd, const char *vptr, size_t n);

        void init_uart();
        int uart_set(int fd, int speed);
        int uart_open(int fd,const char *padthname);
        bool Change_uart_priority();

        //一些更改灯珠颜色的通用接口
        void Set_color_bright(float _bright_ratio)
        {
            bright_ratio = _bright_ratio;
            need_change_color = true;
        }

        float Get_bright_ratio()
        {
            return bright_ratio;
        }

        //初始化一些LED组合
        void Change_LED_Pattern(LED_Pattern _led_pattern)
        {
            if(m_led_pattern != _led_pattern)
            {
                return;
            }
            else
            {
                m_led_pattern = _led_pattern;
                switch (m_led_pattern)
                {
                case full_red :
                    for (int i = 0; i < LED_REGIN; ++i) {
                        LED_list[i][0] = 255; // Red
                        LED_list[i][1] = 0;
                        LED_list[i][2] = 0;
                    }
                    for (int i = LED_REGIN; i < 2 * LED_REGIN; ++i) {
                        LED_list[i][0] = 255;
                        LED_list[i][1] = 0; // Green
                        LED_list[i][2] = 0;
                    }
                    for (int i = 2 * LED_REGIN; i < 3 * LED_REGIN; ++i) {
                        LED_list[i][0] = 255;
                        LED_list[i][1] = 0;
                        LED_list[i][2] = 0; // Blue
                    }
                    break;
                case split_three_color:
                    for (int i = 0; i < LED_REGIN; ++i) {
                        LED_list[i][0] = 255; // Red
                        LED_list[i][1] = 0;
                        LED_list[i][2] = 0;
                    }
                    for (int i = LED_REGIN; i < 2 * LED_REGIN; ++i) {
                        LED_list[i][0] = 0;
                        LED_list[i][1] = 255; // Green
                        LED_list[i][2] = 0;
                    }
                    for (int i = 2 * LED_REGIN; i < 3 * LED_REGIN; ++i) {
                        LED_list[i][0] = 0;
                        LED_list[i][1] = 0;
                        LED_list[i][2] = 255; // Blue
                    }
                    break;
                default:
                    break;
                    need_change_color = true;
                }
            }

        }

    private:
        //串口特征
        int fd;
        const char* uartname;
        int baudrate;
        LED_Pattern m_led_pattern;
        uint8_t LED_list[LED_NUM][LED_DATA] = {0}; 
        float bright_ratio = 1.0f;
};
#endif

//快速排序

