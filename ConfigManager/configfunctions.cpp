#include "configfunctions.h"

QString joinPaths(const QString &path1, const QString &path2)
{
    return QDir::cleanPath(path1 + QDir::separator() + path2);
}

QString simplifyString(const QString &string)
{
    return string.toUpper().replace(" ", "");
}
