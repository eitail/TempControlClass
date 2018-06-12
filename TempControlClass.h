#ifndef TEMPCONTROLCLASS_H
#define TEMPCONTROLCLASS_H

#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QObject>
#include <QDebug>

#include "tempcontrolclass_global.h"
#include "./temperature/temp_thread.h"

class TEMPCONTROLCLASSSHARED_EXPORT TempControlClass
{

    public:
        static TempControlClass* getInstance();
        void        setTempContent(int temp) ;
        int         getTemperture(int temp) ;
        void        setTemperture(int temperturelow, int tempertureup) ;

    private:
        TempControlClass();
        ~TempControlClass();

    private:
        static  TempControlClass*   p;
        thread_temp * m_temperture = NULL;

};

#endif // TEMPCONTROLCLASS_H
