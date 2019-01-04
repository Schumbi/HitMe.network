QT       += core network

TARGET = Hitme.sensor
TEMPLATE = lib
CONFIG += dll

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/sensor \
               $$PWD/../sensor/src

CONFIG += debug_and_release c++11

SOURCES += \
    src/csensor.cpp \
    src/csensorprivate.cpp \
    src/csensordata.cpp \
    src/caccstorage.cpp \
    src/caccdataconverter.cpp

HEADERS += \
    src/csensor.h \
    src/csensorprivate.h \
    src/csensorconfig.h \
    src/csensordata.h \
    src/caccdataconverter.h \
    src/caccstorage.h
