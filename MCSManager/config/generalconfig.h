#ifndef GENERALCONFIG_H
#define GENERALCONFIG_H

#include <QDebug>
#include <QString>
#include <QSettings>

#include "configbase.h"
#include "config/interfaces/igeneralconfig.h"

class GeneralConfig : public ConfigBase, public IGeneralConfig
{
public:
    GeneralConfig(const QString &filePath);
    virtual ~GeneralConfig() {}

    // IGeneralConfig interface
    QString defaultServer() const override;

private:
    void generateConfigFile();

    QVariant readGeneralKey(const QString &key) const;

    void writeGeneralKey(const QString &key, const QVariant &data = QVariant(""));

    //GeneralConfig Constants
    static const QString GENERAL_CONFIG_BASE,
                         DEFAULT_SERVER_KEY;
};

#endif // GENERALCONFIG_H
