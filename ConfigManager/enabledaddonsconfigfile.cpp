#include "enabledaddonsconfigfile.h"

const QString EnabledAddonsConfigFile::GROUP_NAME = QStringLiteral("EnabledAddons");

EnabledAddonsConfigFile::EnabledAddonsConfigFile(const QString &filePath, const QStringList &registeredAddons) :
    ConfigFile(filePath), mRegisteredAddons(registeredAddons)
{
    setGroup(GROUP_NAME);

    foreach (const QString &addonName, mRegisteredAddons)
        setDefaultBool(addonName, false);

    applyDefaults();
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
