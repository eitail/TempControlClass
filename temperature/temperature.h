/*******************************************************************************
Copyright (C), 2017-2020, Shanghai Geant Investment Co., Ltd
File Name: temperature.h
Author: lijianli
Version: v1.0
Date: 2017/11/02
Description:
Notes:
*******************************************************************************/
#ifndef _TEMPERATURE_H
#define _TEMPERATURE_H

#include <ctime>

class Temperature
{
public:
    Temperature(int serialNo);
    ~Temperature();
    bool GetCurrTem(int *tem);
    bool SetLowTem(int low);
    bool SetHighTem(int high);

private:
    unsigned short CRC16_CalcData(unsigned char *data, unsigned short data_len);
    bool SetParam(unsigned short param, unsigned short value);
    
private:
    int m_fd;
    time_t m_time;
};

#endif
