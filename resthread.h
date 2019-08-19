#ifndef RESTHREAD_H
#define RESTHREAD_H

#include <QThread>
#include <QMutex>
class  ResModel:public QObject
{
    Q_OBJECT
public:
    explicit ResModel(QObject *parent=nullptr);

    void closeThread();
signals:
    void finishedMeasure(int val);
public slots:
    void startThreadSlot();
private:
    QMutex mutex;
    volatile bool isStop;
};

#endif // RESTHREAD_H
