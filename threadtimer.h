#ifndef THREADTIMER_H
#define THREADTIMER_H

#include <QThread>

class ThreadTimer : public QThread
{
    Q_OBJECT
public:
    ThreadTimer(int miliseconds, QObject *parent = nullptr);

signals:
    void timeOut();

protected:
    void run() override;

private:
    int mMilisegundos;
};

#endif // THREADTIMER_H
