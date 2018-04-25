#ifndef BACKUPCONFIGREADER_H
#define BACKUPCONFIGREADER_H

#include "mcsmanager/config/interfaces/iconfigfile.h"

#include <QRegularExpression>

class BackupConfigReader
{
public:
    BackupConfigReader(IConfigFile *config);

    QStringList sources() const;
    QString destination() const;

    static ConfigGlobal::ConfigData getDefaults();

private:
    IConfigFile *mConfig;

    //BackupConfigReader constants
    static const QRegularExpression SOURCES_MATCHER;

    static const QString SOURCES_KEY,
                         DESTINATION_KEY;
};

#endif // BACKUPCONFIGREADER_H
