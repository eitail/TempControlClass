/*******************************************************************************
Copyright (C), 2017-2020, Shanghai Geant Investment Co., Ltd
File Name: temperature.cpp
Author: lijianli
Version: v1.0
Date: 2017/11/02
Description:
Notes:
*******************************************************************************/
#include <cstdio>
#include <cstring>
#include <ctime>
#include <assert.h>
#include <unistd.h>
#include "temperature.h"
#include "ssp_serial.h"

static unsigned char g_crc_high[]={
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};
static unsigned char g_crc_low[]={
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};


Temperature::Temperature(int serialNo)
{
    char buff[64] = {0};
    bool bRet;

    sprintf(buff, "/dev/ttyS%d", serialNo);
    m_fd = SSP_OpenPort(buff);
    //assert(m_fd != -1);

    SSP_SetPort(m_fd, 9600);

    m_time = time(NULL);

    //����KP
    bRet = SetParam(0x04, 0);
    //assert(bRet);

    //����AL_P
    bRet = SetParam(0x12, 1);
   // assert(bRet);
}

Temperature::~Temperature()
{
	if( m_fd != -1){
		SSP_ClosePort(m_fd);
	}
    
}

unsigned short Temperature::CRC16_CalcData(unsigned char *data, unsigned short data_len)
{
    unsigned char crc_high    = 0xFF ;
    unsigned char crc_low    = 0xFF ;
    unsigned char i;
    
    while(data_len--)
    {
        i = crc_high ^ *data++;
        crc_high = crc_low ^ g_crc_high[i];
        crc_low = g_crc_low[i];
    }
    
    return (crc_high << 8 | crc_low) ;
}

bool Temperature::SetParam(unsigned short param, unsigned short value)
{
   if( m_fd == -1){ 
      return false;
    }
    unsigned char send_data[8] = {0};
    unsigned char recv_data[8] = {0};
    unsigned short crc;
    time_t begin, end, cur_time;
    int n = 0, len = 0;
    int i = 0;

    while(1)
    {
        cur_time = time(NULL);
        if(cur_time - m_time >= 1)
        {
            break;
        }
        else
        {
            usleep(1000);
        }
    }
    m_time = time(NULL);
    
    send_data[0] = 0x01;
    send_data[1] = 0x06;
    send_data[2] = param / 256;
    send_data[3] = param % 256;
    send_data[4] = value / 256;
    send_data[5] = value % 256;   
    crc = CRC16_CalcData((unsigned char *)send_data, 6);  
    send_data[6] = crc / 256;
    send_data[7] = crc % 256;
    
    //��ӡ��Ϣ
    printf("crc = 0x%04X\n", crc);
    printf("snd: ");
    for(i = 0; i < 8; i++)
    {
        printf("%02X", (unsigned char)send_data[i]);
    }
    printf("\n");
    
    //��������
    if(1 != SSP_WriteData((unsigned char *)send_data, 8, m_fd))
    {
        return false;
    }
    //��������
    begin = time(NULL);
    while(n < 8)
    {
        end = time(NULL);
        if(end - begin > 5)
        {
            break;
        }
        if(SSP_BytesInBuffer(m_fd) > 0)
        {
            len = SSP_ReadData(m_fd, &recv_data[n], 1);
            if(len == 1)
            {
                n++;
            }
        }
        else
        {
            usleep(100);
        }
    }
    if(8 != n)
    {
        return false;
    }
    
    //��ӡ��Ϣ
    printf("rcv: ");
    for(i = 0; i < 8; i++)
    {
        printf("%02X", (unsigned char)recv_data[i]);
    }
    printf("\n");
    
    if(0 != memcmp(send_data, recv_data, 8))
    {

        return false;
    }
    
    return true;
}

bool Temperature::GetCurrTem(int *tem)
{
    if( m_fd == -1){ 
      return false;
    }
    float num;
    int len = 0, n = 0;
    time_t begin, end, cur_time;
    unsigned char get_temperature_cmd[64] = {0x01, 0x03, 0x10, 0x01, 0x00, 0x01, 0xD1, 0x0A};
    unsigned char recv_data[64] = {0};
    int temperature = 0;
    int i;
    
    if(NULL == tem)
    {
        return false;
    }    

    while(1)
    {
        cur_time = time(NULL);
        if(cur_time - m_time >= 1)
        {
            break;
        }
        else
        {
            usleep(1000);
        }
    }
    m_time = time(NULL);

    printf("snd: ");
    for(i = 0; i < 8; i++)
    {
        printf("%02X", (unsigned char)get_temperature_cmd[i]);
    }
    printf("\n");
    //��������
    if(1 != SSP_WriteData(get_temperature_cmd, 8, m_fd))
    {
        return false;
    }
    //��������
    begin = time(NULL);
    while(n < 7)
    {
        end = time(NULL);
        if((end - begin) > 5)
        {
            break;
        }

        if(SSP_BytesInBuffer(m_fd) > 0)
        {
            len = SSP_ReadData(m_fd, &recv_data[n], 1);
            if(len == 1)
            {
                n++;
            }
        }
        else
        {
            usleep(100);
        }
    }
    
    if(7 != n)
    {
        return false;
    }

    printf("rcv: ");
    for(i = 0; i < 7; i++)
    {
        printf("%02X", (unsigned char)recv_data[i]);
    }
    printf("\n");
    
    temperature = (unsigned char)recv_data[3] * 256 + (unsigned char)recv_data[4];
    num = temperature / 10.0;
    printf("temperature: %.1f\n", num);

    *tem = (int)(num + 0.5);
    
    return true;
}


bool Temperature::SetLowTem(int low)
{
    return SetParam(0x00, low * 10);
}

bool Temperature::SetHighTem(int high)
{
    return SetParam(0x01, high * 10);
}

