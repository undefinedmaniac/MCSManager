#include "backupconfigreader.h"

const QRegularExpression BackupConfigReader::SOURCES_MATCHER(QStringLiteral(" *([^;]+?) *(?:;|$)"));

const QString BackupConfigReader::SOURCES_KEY = QStringLiteral("sources"),
              BackupConfigReader::DESTINATION_KEY = QStringLiteral("destination");

BackupConfigReader::BackupConfigReader(IConfigFile *config) : mConfig(config)
{
}

QStringList BackupConfigReader::sources() const
{
    const QString subject = mConfig->readString(SOURCES_KEY);
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
    return mConfig->readString(DESTINATION_KEY);
}

ConfigGlobal::ConfigData BackupConfigReader::getDefaults()
{
    ConfigGlobal::ConfigData data;
    data.append(qMakePair(SOURCES_KEY, QStringLiteral("")));
    data.append(qMakePair(DESTINATION_KEY, QStringLiteral("")));
    return data;
}
