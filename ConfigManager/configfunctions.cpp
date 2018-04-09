#include "configfunctions.h"

QString joinPaths(const QString &path1, const QString &path2)
{
    return QDir::cleanPath(path1 + QDir::separator() + path2);
}

QString simplifyString(const QString &string)
{
    return string.toUpper().simplified();
}

double convertToDouble(const QVariant &data)
{
    bool success = false;

    double result = data.toDouble(&success);

    if (success)
        return result;

    return -1;
}

bool convertToBool(const QVariant &data)
{
    const QString string = simplifyString(data.toString());

    return (string == QStringLiteral("TRUE") || string == QStringLiteral("1"));
}
