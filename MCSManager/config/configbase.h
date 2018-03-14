#ifndef CONFIGBASE_H
#define CONFIGBASE_H

#include <QString>
#include <QSettings>
#include <QDebug>

#include "configfunctions.h"

class ConfigBase
{
public:
    ConfigBase(const QString &filePath);
    virtual ~ConfigBase() { qDebug() << "Config deleted!"; }

protected:
    virtual void generateConfigFile() = 0;

    QSettings &getSettings();
    const QSettings &getSettings() const;

    QVariant readKey(const QString &base, const QString &key) const;

    void writeKey(const QString &base, const QString &key, const QVariant &data = QVariant(""));

    static int convertToInt(const QVariant &data);
    static bool convertToBool(const QVariant &data);

private:
    QSettings mSettings;
};

#endif // CONFIGBASE_H
