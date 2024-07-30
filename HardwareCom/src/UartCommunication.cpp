#include "UartCommunication.hpp"
#include "Timer.h"

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

template <>
void CircularQueue<uint8_t>::printcontent() const {
    if (isEmpty()) {
        fprintf(stderr,"uint8_t quene Empty\n");
        return;
    }
    size_t index = front;
    while (index != rear) {
        std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(arr[index]) << " ";
        index = (index + 1) % capacity;
    }
    std::cout << std::endl;
}

int64_t time_sample_Uartcommunication = 0; 

void UartCom::run()
{
    if (Gloabl_Timer::hasElapsedMs(1000, time_sample_Uartcommunication))
    {
        data_num_pers = data_num;
        data_num = 0;

        m_packet_send_allS = m_packet_send_all;
        m_packet_send_all = 0;
        // std::cout << std::dec << "send_rate " << m_packet_send_allS<< std::endl;
    }

    if (!m_send_buffer.isEmpty())
    {
        //加写锁
        std::unique_lock<std::shared_mutex> send_lock(send_quene_mutex);
        // 处理队列中的元素
        int framesToSend = std::min((int)every_time_send_max, m_send_buffer.size());
        for (int i = 0; i < framesToSend; i++)
        {
            Msg Send_msg = m_send_buffer.dequeue();  // 从队列中取出消息
            // Send_msg.printHex();
            const char* char_data = reinterpret_cast<const char*>(Send_msg.msg_content.data());  // 获取数据
            if(uart_write(fd, char_data, Send_msg.msg_content.size()) > 0)
            {
                ++m_packet_send_all;
            }  // 写入数据
        }
    }
    read_line(fd);
}

void UartCom::init()
{
    Change_uart_priority();
    com_init();
}

void UartCom::cleanup()
{
    close(fd);
}

bool UartCom::Change_uart_priority()
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

void UartCom::com_init()
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

void UartCom::read_line(int fd)
{
    uint8_t *buffer = nullptr;
    size_t buf_size = 0;
    ssize_t total_read = 0;
    ssize_t n;

    do {
        // 扩展缓冲区大小
        if (total_read >= buf_size) {
            buf_size += 512; // 每次增加4096字节
            buffer = (uint8_t *)realloc(buffer, buf_size);
            if (!buffer) {
                fprintf(stderr,"Memory reallocation failed.\n");
            }
        }

        // 从串口读取数据
        n = read(fd, buffer + total_read, buf_size - total_read);
        total_read += n;
    } while (n > 0);
    
    uint32_t total_read_num = ssize_t_to_uint32_t(total_read);
    //把数据压入循环队列
    if(total_read_num > 0)
    {
        m_recieve_buffer.enqueue(buffer,total_read_num);
        data_num+=total_read_num;
    }

    // 使用完毕后释放内存
    free(buffer);
    buffer = nullptr;
}
 
ssize_t UartCom::safe_write(int fd, const char *vptr, size_t n)
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

int UartCom::uart_write(int fd,const char *w_buf,size_t len)
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

int UartCom::uart_open(int fd,const char *pathname){
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

//设置自定义波特率接口
int UartCom::uart_set(int fd, int speed) {
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

