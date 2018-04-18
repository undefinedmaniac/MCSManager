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
    mcsmanager/config/configfile.cpp \
    mcsmanager/config/configfilefactory.cpp \
    mcsmanager/config/configfunctions.cpp \
    mcsmanager/config/configmanager.cpp \
    mcsmanager/config/serverconfig.cpp \
    mcsmanager/config/serverconfigfactory.cpp \
    mcsmanager/mcserver/server/mcserver.cpp \
    mcsmanager/mcserver/server/serverconfigreader.cpp \
    mcsmanager/core/mcsmanagercorechild.cpp \
    mcsmanager/mcserver/addons/sleeperaddon.cpp \
    mcsmanager/mcserver/addons/mcserveraddonbase.cpp \
    mcsmanager/mcserver/addons/sleeperconfigreader.cpp

HEADERS += \
    mcsmanager/config/interfaces/iconfigfile.h \
    mcsmanager/config/interfaces/iconfigmanager.h \
    mcsmanager/config/interfaces/iserverconfig.h \
    mcsmanager/config/configfile.h \
    mcsmanager/config/configfilefactory.h \
    mcsmanager/config/configfunctions.h \
    mcsmanager/config/configglobal.h \
    mcsmanager/config/configmanager.h \
    mcsmanager/config/serverconfig.h \
    mcsmanager/config/serverconfigfactory.h \
    mcsmanager/mcserver/server/interfaces/imcserver.h \
    mcsmanager/mcserver/addons/interfaces/imcserveraddon.h \
    mcsmanager/mcserver/server/mcserver.h \
    mcsmanager/mcserver/server/serverconfigreader.h \
    mcsmanager/core/interfaces/imcsmanagercore.h \
    mcsmanager/core/mcsmanagercorechild.h \
    mcsmanager/mcserver/addons/sleeperaddon.h \
    mcsmanager/mcserver/addons/mcserveraddonbase.h \
    mcsmanager/mcserver/addons/sleeperconfigreader.h
