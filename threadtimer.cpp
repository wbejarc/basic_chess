#include "threadtimer.h"

ThreadTimer::ThreadTimer(int milisegundos, QObject *parent)
    : QThread(parent)
{
    mMilisegundos = milisegundos;
}

void ThreadTimer::run()
{
    while(true)
    {
        emit timeOut();
        QThread::msleep(mMilisegundos);
    }
}
