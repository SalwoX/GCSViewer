#include "process.h"
#include <QObject>
#include <QDebug>
#include <QThread>
#include <unistd.h>


unsigned int microsecond = 1000000;

Process::Process (QObject *parent) : QObject(parent)
{

}


void Process::doWork()
{
    while(true) {

        dbManager.getReply ();
        usleep (1*microsecond);
        qDebug() << dbManager.getVSpeed();
    }
}

void Process::setUp (QThread &thread) {
    connect (&thread, SIGNAL(started()),this, SLOT(doWork()));
    connect (&thread, SIGNAL(finished()),this, SLOT(deleteLater()));
}
