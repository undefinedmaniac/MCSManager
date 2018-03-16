#ifndef ILOGREADER_H
#define ILOGREADER_H

class QByteArray;
class ILogReaderAddonConfig;

class ILogReader
{
public:
    virtual ~ILogReader() {}

    virtual void setConfig(const ILogReaderAddonConfig *config) = 0;
    virtual const ILogReaderAddonConfig *config() const = 0;

    virtual QByteArray readAll(int startPos = 0) const = 0;
    virtual int size() const = 0;
    virtual void clear() = 0;

signals:
    virtual void newData(int startPos) = 0;
};

Q_DECLARE_INTERFACE(ILogReader, "ILogReader")

#endif // ILOGREADER_H
