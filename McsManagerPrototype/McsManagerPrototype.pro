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
    core/mcsmanagermediator.cpp \
    config/configmanager.cpp \
    config/serverconfig.cpp \
    config/backupserviceconfig.cpp

HEADERS += \
    config/interface/iserverconfig.h \
    config/interface/imcscpclientconfig.h \
    config/interface/iserversleeperconfig.h \
    config/interface/ibackupserviceconfig.h \
    config/interface/igeneralconfig.h \
    config/interface/irestarterconfig.h \
    config/interface/ibackupmanagerconfig.h \
    config/interface/iconfigmanager.h \
    core/interface/imcsmanagermediator.h \
    core/mcsmanagermediator.h \
    config/configmanager.h \
    config/serverconfig.h \
    config/backupserviceconfig.h
