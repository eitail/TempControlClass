/*******************************************************************************
Copyright (C), 2012-2016, Shanghai Geant Investment Co., Ltd
File Name: ssp_serial.c
Author: lijianli
Version: v1.0
Date: 2015/08/27
Description:
Notes:
*******************************************************************************/
#include "ssp_serial.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>


/*******************************************************************************
Function Name: SSP_OpenPort
Description: 打开串口
Inputs: port: 串口 标识
Outputs: N/A
Return: 成功返回串口描述符，失败返回-1
Notes: 串口以非阻塞模式打开
*******************************************************************************/
SSP_PORT SSP_OpenPort(const char * port)
{
    int port_handle;
    
    port_handle = open(port,O_RDWR| O_NOCTTY | O_NDELAY);
    if(port_handle == -1)
    {
        perror("Unable to open port");
    }
    else
    {
        fcntl(port_handle,F_SETFL,1);
    }
    
    return port_handle;
}



/*******************************************************************************
Function Name: SSP_ClosePort
Description: 关闭串口
Inputs: port: 串口描述符
Outputs: N/A
Return: N/A
Notes:
*******************************************************************************/
void SSP_ClosePort(const SSP_PORT port)
{
    if(port >= 0)
    {
        close(port);
    }
}


/*******************************************************************************
Function Name: SSP_WriteData
Description: 向串口写数据
Inputs: data: 数据, length: 数据长度, port: 串口描述符
Outputs: N/A
Return: success: 1, fail: 0
Notes:
*******************************************************************************/
int SSP_WriteData(const unsigned char * data, unsigned long length, const SSP_PORT port)
{
    long n;
    long offset;
    long bytes_left = length;
    offset = 0;

    //printf("OUT: ");
    //for (n = 0; n < length; ++n)
    //printf("%c",(unsigned char)data[n]);
    //printf("\n");

    while(bytes_left > 0)
    {
        while(SSP_TransmitComplete(port) == 0)
        {
            usleep(100);
        }
        n = write(port, &data[offset], bytes_left);
        usleep(500);
        if(n < 0)
        {
            perror("Write Port Failed");
            return 0;
        }
        offset += n;
        bytes_left -= n;
    }
    
    return 1;
}


/*******************************************************************************
Function Name: SSP_SetPort
Description: 设置串口
Inputs: port: 串口描述符
Outputs: N/A
Return: N/A
Notes:
*******************************************************************************/
void SSP_SetPort(const SSP_PORT port, int baund)
{
    struct termios options;
    
    tcgetattr(port,&options);
    
    //9600 baud
    switch(baund)
    {
    case 9600:
        cfsetispeed(&options,B9600);
        cfsetospeed(&options,B9600);
        break;
    case 38400:
        cfsetispeed(&options,B38400);
        cfsetospeed(&options,B38400);
        break;
    default:
        cfsetispeed(&options,B9600);
        cfsetospeed(&options,B9600); 
    }
    
    //no parity
    options.c_cflag &= ~PARENB;

    // 2 stop bits
    options.c_cflag |= CSTOPB;
    //options.c_cflag &= ~CSTOPB;

    //8 bits
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    
    //raw binary input / output
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;
    
    //no flow control
    options.c_iflag = 0;
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_cflag &= ~CRTSCTS;
    
    
    options.c_cflag |= (CLOCAL | CREAD);
    fcntl(port, F_SETFL, FNDELAY);
    tcsetattr(port,TCSANOW,&options);
    
}



/*******************************************************************************
Function Name: SSP_BytesInBuffer
Description: 串口接收缓冲区中已接收字节数
Inputs: port: 串口描述符
Outputs: N/A
Return: 已结束字节数
Notes:
*******************************************************************************/
int SSP_BytesInBuffer(SSP_PORT port)
{
    int bytes;
    
    ioctl(port,FIONREAD,&bytes);
    
    return bytes;
}


/*******************************************************************************
Function Name: SSP_TransmitComplete
Description: 串口是否已发完数据
Inputs: port: 串口描述符
Outputs: N/A
Return: sucess: TRUE, fail: FALSE
Notes:
*******************************************************************************/
int SSP_TransmitComplete(SSP_PORT port)
{
    int bytes;
    
    ioctl(port,TIOCOUTQ,&bytes);
    
    return (bytes == 0);
}


/*******************************************************************************
Function Name: SSP_ReadData
Description: 读取串口数据
Inputs: port: 串口描述符,  bytes_to_read: 缓冲区大小
Outputs: buffer: 接收缓冲区
Return: sucess: 读取字节数, fail: -1
Notes:
*******************************************************************************/
int SSP_ReadData(const SSP_PORT port, unsigned char * buffer, unsigned long bytes_to_read)
{
    return read(port,buffer,bytes_to_read);
}


