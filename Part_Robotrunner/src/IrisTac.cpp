#include "IrisTac.hpp"

#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <asm/termbits.h>
#include <string.h>

void IrisTac::Camera_control()
{

}

void IrisTac::LED_control()
{
    if(need_change_color)
    {
        need_change_color = false;
        ChangeColor();
    }
}

void IrisTac::init_uart()
{
    Change_uart_priority();
    com_init();
}

void IrisTac::com_init()
{
    fd = uart_open(fd,uartname);
    if(fd == -1)
    {
        fprintf(stderr,"uart_open error\n");
        exit(EXIT_FAILURE);
    }
    if(uart_set(fd,baudrate) == -1)
    {
        fprintf(stderr,"uart set failed!\n");
        exit(EXIT_FAILURE);
    }
}


ssize_t IrisTac::safe_write(int fd, const char *vptr, size_t n)
{
    size_t  nleft;
    ssize_t nwritten;
    const char *ptr;
 
    ptr = vptr;
    nleft = n;
 
    while(nleft > 0)
    {
    if((nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if(nwritten < 0&&errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;
        ptr   += nwritten;
    }
    return(n);
}

int IrisTac::uart_write(int fd,const char *w_buf,size_t len)
{
    ssize_t cnt = 0;
    cnt = safe_write(fd,w_buf,len);
    if(cnt == -1)
    {
        // fprintf(stderr,"write error!\n");
        return -1;
    }
    return cnt;
}

int IrisTac::uart_open(int fd,const char *pathname){
    assert(pathname);
    /*打开串口*/
    fd = open(pathname,O_RDWR|O_NOCTTY|O_NDELAY);
    if(fd == -1)
    {
        perror("Open UART failed!");
        return -1;
    }
    return fd;
}

bool IrisTac::Change_uart_priority()
{
    std::string command = "sudo chmod 777 " + std::string(uartname);

    // 执行系统命令
    int result = std::system(command.c_str());

    if (result != 0) {
        std::cerr << "Failed to execute command: " << command << std::endl;
        return true;
    }

    std::cout << "Command executed successfully: " << command << std::endl;
    return false;
}

int IrisTac::uart_set(int fd, int speed) {
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
  //VTIME 为1，表示读取超时时间为0秒。有数据就返回，没数据就返回0
  tty.c_cc[VMIN] = 0;   
  tty.c_cc[VTIME] = 0;  
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