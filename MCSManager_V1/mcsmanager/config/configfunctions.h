#ifndef CONFIGFUNCTIONS_H
#define CONFIGFUNCTIONS_H

#include "configglobal.h"

#include <QVariant>
#include <QString>
#include <QDir>

/**
 * @brief joinPaths Joins two paths together
 * @param path1 The first path
 * @param path2 The second path
 * @return The combined paths
 */
QString joinPaths(const QString &path1, const QString &path2);

/**
 * @brief simplifyString Simplifys a string by uppercasing it and
 * removing unneeded whitespace
 * @param string The string to simplify
 * @return The simplified string
 */
QString simplifyString(const QString &string);

/**
 * @brief convertToDouble Converts a QVariant to a double
 * @param data The QVariant
 * @return The double on success, -1 on failure
 */
double convertToDouble(const QVariant &data);

/**
 * @brief convertToBool Converts a QVariant to a boolean.
 * If the simplified string value of the QVariant is equal to
 * "TRUE" or "1", this function will return true. Otherwise, it will
 * return false.
 * @param data The QVariant
 * @return The boolean
 */
bool convertToBool(const QVariant &data);

/**
 * @brief convertToShutdownBehavior Converts a string to a ShutdownBehavior
 * If the simplified value is equal to "DONOTHING", "RESTART", or "STARTALTSERVER"
 * respectively, the value will be converted to the associated enum value.
 * Otherwise, the function will return ShutdownBehavior::DoNothing.
 * @param data The string
 * @return The ShutdownBehavior
 */
Config::ShutdownBehavior convertToShutdownBehavior(const QString &data);

#endif // CONFIGFUNCTIONS_H
