#include "TempControlClass.h"


TempControlClass::TempControlClass()
{
}

TempControlClass::~TempControlClass()
{
    if(m_temperture  != NULL){
        delete m_temperture;
    }
}

TempControlClass* TempControlClass::p = NULL;
TempControlClass* TempControlClass::getInstance()
{
    if( p == NULL )
    {
        p = new TempControlClass();
    }
    return p;
}

void TempControlClass::setTempContent(int temp)
{
    if(m_temperture  == NULL){
        m_temperture = new thread_temp(temp);;
    }
}

int TempControlClass::getTemperture(int temp)
{
    int temps = temp;
    if(m_temperture != NULL){

        m_temperture->getTemperture(&temps);

    }
   return temps;
}

void TempControlClass::setTemperture(int temperturelow, int tempertureup)
{
    qDebug() << "temperturelow" << QString::number(temperturelow);
    qDebug() << "temperturelow" << QString::number(tempertureup);
//    if(m_temperture != NULL){
//        m_temperture->setTemperture(temperturelow,tempertureup);
//    }

}
