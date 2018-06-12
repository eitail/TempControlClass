#include "temp_thread.h"
#include <qdebug.h>
#include <qdatetime.h>

thread_temp::thread_temp(int com_no):my_temperature(NULL)
{
    qDebug()<<"init thread_temp";
    //newadd
    my_temperature = new Temperature(com_no);
}

void thread_temp::setType(QString type)
{
    myType = type;
}

//设置温度  temperture_low:最低温度  temperture_up:最高温度
void thread_temp::setTemperture(int temperture_low,int temperture_up)
{
    if(my_temperature != NULL){
        if(!my_temperature->SetHighTem(temperture_up)){

        }

        if(!my_temperature->SetLowTem(temperture_low)){
        }
    }

}

//获取当前温度
void thread_temp::getTemperture(int* temperture)
{
    if(my_temperature != NULL){

        if(!my_temperature->GetCurrTem(temperture)){

        }
    }
}


void thread_temp::run()
{

}
