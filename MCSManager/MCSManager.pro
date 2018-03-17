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

SOURCES += \
    config/configbase.cpp \
    config/configfunctions.cpp \
    config/configmanager.cpp \
    config/generalconfig.cpp \
    config/serverconfig.cpp \
    server/minecraftserver.cpp \
    main.cpp \
    core/mcsmanagercore.cpp \
    server/manager/minecraftservermanager.cpp \
    core/mcsmanagercorebase.cpp \
    server/builder/minecraftserverbuilder.cpp \
    server/addons/logreader.cpp \
    server/addons/minecraftserveraddonbase.cpp \
    server/addons/minecraftserveraddonfactory.cpp \
    server/addons/restarterservice.cpp

HEADERS += \
    config/interfaces/ibackupaddonconfig.h \
    config/interfaces/iconfigmanager.h \
    config/interfaces/igeneralconfig.h \
    config/interfaces/ilogreaderaddonconfig.h \
    config/interfaces/imcscpaddonconfig.h \
    config/interfaces/irestarteraddonconfig.h \
    config/interfaces/iserverbackupconfig.h \
    config/interfaces/iserverconfig.h \
    config/interfaces/iservermanagerconfig.h \
    config/interfaces/isleeperaddonconfig.h \
    config/configbase.h \
    config/configfunctions.h \
    config/configmanager.h \
    config/generalconfig.h \
    config/serverconfig.h \
    server/addons/interfaces/iminecraftserveraddon.h \
    server/addons/interfaces/iminecraftserveraddonfactory.h \
    server/builder/interfaces/iminecraftserverbuilder.h \
    server/interfaces/iminecraftserver.h \
    server/interfaces/iminecraftserveraddonmanager.h \
    server/interfaces/iminecraftserverio.h \
    server/interfaces/iminecraftserverprocess.h \
    server/minecraftserver.h \
    core/interfaces/icurrentserverinterface.h \
    core/interfaces/imcsmanagercore.h \
    core/interfaces/imcsmanagercorebase.h \
    core/interfaces/imcsmanagerinterface.h \
    core/mcsmanagercore.h \
    server/manager/interfaces/iminecraftservermanager.h \
    server/manager/minecraftservermanager.h \
    core/mcsmanagercorebase.h \
    server/builder/minecraftserverbuilder.h \
    server/addons/interfaces/iserversleeper.h \
    server/addons/interfaces/irestarterservice.h \
    server/addons/interfaces/ibackupservice.h \
    server/addons/interfaces/imcscpclient.h \
    server/addons/interfaces/ilogreader.h \
    server/addons/logreader.h \
    server/addons/minecraftserveraddonbase.h \
    server/addons/minecraftserveraddonfactory.h \
    server/addons/restarterservice.h
