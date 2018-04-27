#ifndef ICONFIGFILE_H
#define ICONFIGFILE_H

#include "../configglobal.h"

class QString;

namespace Config { class IConfigFile; }

class Config::IConfigFile
{
public:
    virtual ~IConfigFile() {}

    /**
     * @brief setGroup Sets a prefix to add before all keys
     * @param group The prefix
     */
    virtual void setGroup(const QString &group) = 0;

    /**
     * @brief readString Read string data
     * @param key The key to read
     * @return The string data
     */
    virtual QString readString(const QString &key) const = 0;

    /**
     * @brief readBool Read boolean data
     * @param key The key to read
     * @return The boolean data
     */
    virtual bool readBool(const QString &key) const = 0;

    /**
     * @brief readDouble Read double data
     * @param key The key to read
     * @return The double data
     */
    virtual double readDouble(const QString &key) const = 0;

    /**
     * @brief writeString Write string data
     * @param key The key to write
     * @param value The string data
     */
    virtual void writeString(const QString &key, const QString &value) = 0;

    /**
     * @brief writeBool Write boolean data
     * @param key The key to write
     * @param value The boolean data
     */
    virtual void writeBool(const QString &key, bool value) = 0;

    /**
     * @brief writeDouble Write double data
     * @param key The key to write
     * @param value The double data
     */
    virtual void writeDouble(const QString &key, double value) = 0;

    /**
     * @brief applyDefaults Apply a list of default keys and values to the
     * config file
     * @param defaults The list of default keys and values
     */
    virtual void applyDefaults(const Config::ConfigData &defaults) = 0;
};

#endif // ICONFIGFILE_H
