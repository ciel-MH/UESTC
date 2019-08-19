#ifndef CAPTHREAD_H
#define CAPTHREAD_H
#include <QThread>
#include <QMutex>
class  CapModel:public QObject
{
    Q_OBJECT
public:
    explicit CapModel(QObject *parent=nullptr);

    void closeThread();
signals:
    void finishedMeasure(int val);
public slots:
    void startThreadSlot();
private:
    QMutex mutex;
    volatile bool isStop;
};

#endif // CAPTHREAD_H
