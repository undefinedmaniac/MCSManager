#include "commandlinewriter.h"

using Cli::CommandLineWriter;

CommandLineWriter::CommandLineWriter(QObject *parent) : QObject(parent), mOutput(stdout)
{
}

void CommandLineWriter::writeChars(const QString &chars)
{
    mOutput << chars;
    mOutput.flush();
}

void CommandLineWriter::writeLine(const QString &line)
{    
    const QString trimmedLine = line.trimmed();
    mOutput << trimmedLine << endl;
    mOutput.flush();
}

void CommandLineWriter::writeLines(const QStringList &lines)
{
    foreach (const QString &line, lines)
        writeLine(line);
}

void CommandLineWriter::setPrefix(const QString &prefix)
{
    mPrefix = prefix;
}

void CommandLineWriter::writePrefix()
{
    mOutput << '[' % mPrefix % "]: ";
    mOutput.flush();
}

void CommandLineWriter::erasePrefix()
{
    int length = mPrefix.size() + 4;

    QString eraseString;
    eraseString.reserve(length + 2);
    eraseString += '\r';
    for (int i = 0; i < length; i++)
        eraseString += ' ';
    eraseString += '\r';

    writeChars(eraseString);
}


