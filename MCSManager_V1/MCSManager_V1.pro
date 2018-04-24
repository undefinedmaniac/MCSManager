QT -= gui
QT += network

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
    mcsmanager/config/configfile.cpp \
    mcsmanager/config/configfilefactory.cpp \
    mcsmanager/config/configfunctions.cpp \
    mcsmanager/config/configmanager.cpp \
    mcsmanager/config/serverconfig.cpp \
    mcsmanager/config/serverconfigfactory.cpp \
    mcsmanager/core/mcsmanagercorechild.cpp \
    mcsmanager/mcserver/addons/mcscp/mcscpaddon.cpp \
    mcsmanager/mcserver/addons/mcscp/mcscpconfigreader.cpp \
    mcsmanager/mcserver/addons/mcserveraddonbase.cpp \
    mcsmanager/mcserver/server/mcserver.cpp \
    mcsmanager/mcserver/server/serverconfigreader.cpp \
    main.cpp \
    mcsmanager/mcserver/addons/mcscp/mcscphandshake.cpp \
    mcsmanager/mcserver/addons/mcscp/mcscpservertable.cpp \
    mcsmanager/mcserver/addons/restarter/restarteraddon.cpp \
    mcsmanager/mcserver/addons/restarter/restarterconfigreader.cpp \
    mcsmanager/mcserver/addons/sleeper/sleeperaddon.cpp \
    mcsmanager/mcserver/addons/mcscp/mcscpplayertable.cpp \
    mcsmanager/mcserver/addons/sleeper/sleeperconfigreader.cpp \
    mcsmanager/mcsmanagerapplication.cpp \
    mcsmanager/backup/backupmanager.cpp \
    mcsmanager/backup/backupprocess.cpp \
    mcsmanager/backup/backupconfigreader.cpp \
    mcsmanager/core/mcsmanagercore.cpp \
    mcsmanager/mcserver/mcserverbuilder.cpp

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
    mcsmanager/core/interfaces/imcsmanagercore.h \
    mcsmanager/core/mcsmanagercorechild.h \
    mcsmanager/mcserver/addons/interfaces/imcserveraddon.h \
    mcsmanager/mcserver/addons/mcscp/mcscpaddon.h \
    mcsmanager/mcserver/addons/mcscp/mcscpconfigreader.h \
    mcsmanager/mcserver/addons/mcserveraddonbase.h \
    mcsmanager/mcserver/server/interfaces/imcserver.h \
    mcsmanager/mcserver/server/mcserver.h \
    mcsmanager/mcserver/server/serverconfigreader.h \
    mcsmanager/mcserver/addons/mcscp/mcscphandshake.h \
    mcsmanager/mcserver/addons/mcscp/mcscpservertable.h \
    mcsmanager/mcserver/addons/mcscp/interfaces/imcscpservertable.h \
    mcsmanager/mcserver/addons/mcscp/interfaces/imcscpaddon.h \
    mcsmanager/mcserver/addons/restarter/restarteraddon.h \
    mcsmanager/mcserver/addons/restarter/restarterconfigreader.h \
    mcsmanager/mcserver/addons/sleeper/sleeperaddon.h \
    mcsmanager/mcserver/addons/mcscp/interfaces/imcscpplayertable.h \
    mcsmanager/mcserver/addons/mcscp/mcscpplayertable.h \
    mcsmanager/mcserver/addons/sleeper/sleeperconfigreader.h \
    mcsmanager/mcsmanagerapplication.h \
    mcsmanager/backup/backupmanager.h \
    mcsmanager/backup/interfaces/ibackupmanager.h \
    mcsmanager/backup/interfaces/ibackupprocess.h \
    mcsmanager/backup/backupprocess.h \
    mcsmanager/backup/backupconfigreader.h \
    mcsmanager/core/mcsmanagercore.h \
    mcsmanager/mcserver/interfaces/imcserverbuilder.h \
    mcsmanager/mcserver/mcserverbuilder.h
