#-------------------------------------------------
#
# Project created by QtCreator 2018-06-12T10:25:47
#
#-------------------------------------------------

QT       -= gui

TARGET = TempControlClass
TEMPLATE = lib

DEFINES += TEMPCONTROLCLASS_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        TempControlClass.cpp \
    temperature/ssp_serial.cpp \
    temperature/temperature.cpp \
    temperature/temp_thread.cpp

HEADERS += \
        TempControlClass.h \
        tempcontrolclass_global.h \ 
    temperature/ssp_serial.h \
    temperature/temperature.h \
    temperature/temp_thread.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
