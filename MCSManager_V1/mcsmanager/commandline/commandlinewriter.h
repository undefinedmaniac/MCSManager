#ifndef COMMANDLINEWRITER_H
#define COMMANDLINEWRITER_H

#include <QObject>
#include <QTextStream>
#include <QDebug>
#include <QStringBuilder>

namespace Cli { class CommandLineWriter; }

class Cli::CommandLineWriter : public QObject
{
    Q_OBJECT
public:
    CommandLineWriter(QObject *parent = nullptr);

    void writeChars(const QString &chars);

    void writeLine(const QString &line);
    void writeLines(const QStringList &lines);

    void setPrefix(const QString &prefix);
    void writePrefix();
    void erasePrefix();

private:
    QTextStream mOutput;
    QString mPrefix;
};

#endif // COMMANDLINEWRITER_H
