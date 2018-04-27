#include "backupconfigreader.h"

using Backup::BackupConfigReader;

const QRegularExpression BackupConfigReader::SOURCES_MATCHER(QStringLiteral(" *([^;]+?) *(?:;|$)"));

BackupConfigReader::BackupConfigReader(Config::IConfigFile *config) : mConfig(config)
{
}

QStringList BackupConfigReader::sources() const
{
    const QString subject = mConfig->readString(Backup::SOURCES_KEY);
    QRegularExpressionMatchIterator iterator = SOURCES_MATCHER.globalMatch(subject);
    QStringList list;

    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString string = match.captured(1);
        if (!string.isNull())
            list.append(string);
    }

    return list;
}

QString BackupConfigReader::destination() const
{
    return mConfig->readString(Backup::DESTINATION_KEY);
}
