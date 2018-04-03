#include "enabledaddonsconfigfile.h"

const QString EnabledAddonsConfigFile::GROUP_NAME = QStringLiteral("EnabledAddons");

EnabledAddonsConfigFile::EnabledAddonsConfigFile(const QString &filePath, const QStringList &registeredAddons) :
    ConfigFile(filePath), mRegisteredAddons(registeredAddons)
{
    setGroup(GROUP_NAME);

    QHash<QString, QString> defaults;

    foreach (const QString &addonName, mRegisteredAddons)
        defaults.insert(addonName, QStringLiteral("false"));

    applyDefaults(defaults);
}

QStringList EnabledAddonsConfigFile::getEnabledAddons()
{
    QStringList enabledAddons;

    foreach (const QString &addonName, mRegisteredAddons) {
        if (readBool(addonName))
            enabledAddons.append(addonName);
    }

    return enabledAddons;
}
