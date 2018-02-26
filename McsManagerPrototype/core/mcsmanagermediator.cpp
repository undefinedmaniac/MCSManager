#include "mcsmanagermediator.h"

McsManagerMediator::McsManagerMediator(QObject *parent) : QObject(parent)
{

}

McsManagerMediator::~McsManagerMediator()
{
    stopApplication();
}

void McsManagerMediator::startApplication()
{
    emit started();
}

void McsManagerMediator::stopApplication()
{
    emit stopped();
}
