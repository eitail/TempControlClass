/*******************************************************************************
Copyright (C), 2012-2016, Shanghai Geant Investment Co., Ltd
File Name: ssp_serial.h
Author: lijianli
Version: v1.0
Date: 2015/08/27
Description:
Notes:
*******************************************************************************/
#ifndef _SSP_SERIAL_H
#define _SSP_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int SSP_PORT;


/*******************************************************************************
Function Name: SSP_OpenPort
Description: 打开串口
Inputs: port: 串口 标识
Outputs: N/A
Return: 成功返回串口描述符，失败返回-1
Notes: 串口以非阻塞模式打开
*******************************************************************************/
SSP_PORT SSP_OpenPort(const char * port);


/*******************************************************************************
Function Name: SSP_ClosePort
Description: 关闭串口
Inputs: port: 串口描述符
Outputs: N/A
Return: N/A
Notes:
*******************************************************************************/
void SSP_ClosePort(const SSP_PORT port);


/*******************************************************************************
Function Name: SSP_WriteData
Description: 向串口写数据
Inputs: data: 数据, length: 数据长度, port: 串口描述符
Outputs: N/A
Return: success: 1, fail: 0
Notes:
*******************************************************************************/
int SSP_WriteData(const unsigned char * data, unsigned long length, const SSP_PORT port);


/*******************************************************************************
Function Name: SSP_SetPort
Description: 设置串口
Inputs: port: 串口描述符
Outputs: N/A
Return: N/A
Notes:
*******************************************************************************/
void SSP_SetPort(const SSP_PORT port, int baund);


/*******************************************************************************
Function Name: SSP_BytesInBuffer
Description: 串口接收缓冲区中已接收字节数
Inputs: port: 串口描述符
Outputs: N/A
Return: 已结束字节数
Notes:
*******************************************************************************/
int SSP_BytesInBuffer(SSP_PORT port);


/*******************************************************************************
Function Name: SSP_TransmitComplete
Description: 串口是否已发完数据
Inputs: port: 串口描述符
Outputs: N/A
Return: sucess: TRUE, fail: FALSE
Notes:
*******************************************************************************/
int SSP_TransmitComplete(SSP_PORT port);


/*******************************************************************************
Function Name: SSP_ReadData
Description: 读取串口数据
Inputs: port: 串口描述符,  bytes_to_read: 缓冲区大小
Outputs: buffer: 接收缓冲区
Return: sucess: 读取字节数, fail: -1
Notes:
*******************************************************************************/
int SSP_ReadData(const SSP_PORT port, unsigned char * buffer, unsigned long bytes_to_read);


#ifdef __cplusplus
}
#endif

#endif
