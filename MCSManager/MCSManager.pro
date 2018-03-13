QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    config/serverconfig.cpp \
    config/generalconfig.cpp \
    config/configbase.cpp \
    config/configmanager.cpp

HEADERS += \
    config/interfaces/iserverconfig.h \
    config/interfaces/iserverbackupconfig.h \
    config/interfaces/ibackupaddonconfig.h \
    config/interfaces/irestarteraddonconfig.h \
    config/interfaces/iservermanagerconfig.h \
    config/interfaces/isleeperaddonconfig.h \
    config/interfaces/imcscpaddonconfig.h \
    config/serverconfig.h \
    config/interfaces/ilogreaderaddonconfig.h \
    config/interfaces/igeneralconfig.h \
    config/generalconfig.h \
    config/configbase.h \
    config/interfaces/iconfigmanager.h \
    config/configmanager.h
