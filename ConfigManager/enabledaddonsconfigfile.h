#ifndef ENABLEDADDONSCONFIGFILE_H
#define ENABLEDADDONSCONFIGFILE_H

#include "ienabledaddons.h"
#include "configfile.h"

class EnabledAddonsConfigFile : public ConfigFile, public IEnabledAddons
{
public:
    EnabledAddonsConfigFile(const QString &filePath, const QStringList &registeredAddons);

    // IEnabledAddons interface
    QStringList getEnabledAddons() override;

private:
    const QStringList mRegisteredAddons;

    static const QString GROUP_NAME;
};

#endif // ENABLEDADDONSCONFIGFILE_H
