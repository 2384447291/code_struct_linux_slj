#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <termios.h>
#include <math.h>
#include <pthread.h>
#include <stropts.h>
#include <endian.h>
#include <stdint.h>

#include "rt_serial.h"

//设置自定义波特率接口
int set_interface_attribs_custom_baud(int fd, int speed, int parity, int port) {
  (void)parity;
  (void)port;

  printf("\t[RT SERIAL] Configuring serial device...\n");
  struct termios2 tty;
  //使用 ioctl 系统调用获取当前串行端口的设置，
  //并存储到 tty 结构体中。
  //TCGETS2 是一个标志，表示获取 termios2 结构体。
  ioctl(fd, TCGETS2, &tty);
  //清除 c_cflag 中的波特率标志（CBAUD），
  //然后设置为允许自定义波特率（BOTHER）。
  tty.c_cflag &= ~CBAUD;
  tty.c_cflag |= BOTHER;
  //清零对应数据位并重新设置为8位
  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;  

  //设置输入和输出的波特率为 speed
  tty.c_ispeed = speed;
  tty.c_ospeed = speed;

  //禁用 IGNBRK 标志，以便在波特率不匹配时不忽略断点符（break characters）
  tty.c_iflag &= ~IGNBRK; 
  //清除 c_lflag，禁用所有本地模式标志（无信号字符，无回显，无规范处理）
  tty.c_lflag = 0;     
  //清除 c_oflag，禁用所有输出模式标志（无重新映射，无延迟）
  tty.c_oflag = 0;      
  //设置控制字符数组中的 VMIN 为0，表示读取时不阻塞；
  //VTIME 为1，表示读取超时时间为0.1秒。
  tty.c_cc[VMIN] = 0;   
  tty.c_cc[VTIME] = 1;  
  //禁用软件流控制（IXON、IXOFF、IXANY）
  tty.c_iflag &= ~(IXON | IXOFF | IXANY);  

  //设置 c_cflag，忽略调制解调器控制线（CLOCAL），并启用接收器（CREAD）
  tty.c_cflag |= (CLOCAL | CREAD); 
  //关闭奇偶校验（PARENB），并且清除任何奇偶校验类型设置（PARODD）
  //设置为一位停止位（清除 CSTOPB）
  //禁用硬件流控制（清除 CRTSCTS）
  tty.c_cflag &= ~(PARENB | PARODD);     
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CRTSCTS;
  // cfmakeraw(&tty);

  //使用 ioctl 系统调用将配置的设置应用到串行端口,同上
  ioctl(fd, TCSETS2, &tty);
  return 0;
}

#endif
