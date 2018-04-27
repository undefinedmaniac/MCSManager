#ifndef BACKUPCONFIGREADER_H
#define BACKUPCONFIGREADER_H

#include "mcsmanager/backup/backupglobal.h"
#include "mcsmanager/config/interfaces/iconfigfile.h"

#include <QRegularExpression>

namespace Backup { class BackupConfigReader; }

class Backup::BackupConfigReader
{
public:
    BackupConfigReader(Config::IConfigFile *config);

    QStringList sources() const;
    QString destination() const;

private:
    Config::IConfigFile *mConfig;

    //BackupConfigReader constants
    static const QRegularExpression SOURCES_MATCHER;
};

#endif // BACKUPCONFIGREADER_H
