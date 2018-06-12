#ifndef THREAD_TEMP_H
#define THREAD_TEMP_H
#include <QThread>
#include "temperature.h"


class thread_temp : public QThread
{
    Q_OBJECT
public:
    explicit thread_temp(int com_no);
    void setType(QString type);
    void setTemperture(int temperture_low,int temperture_up);
    void getTemperture(int* temperture);

protected:
    void run();

private:

    Temperature* my_temperature ;
    QString myType;

};

#endif // THREAD_TEMP_H
