#ifndef RESCAPMEASUREMENTMODEL_H
#define RESCAPMEASUREMENTMODEL_H
#include <QObject>
#include "capthread.h"
#include "resthread.h"

#define MEASURETYPE_RES (1)
#define MEASURETYPE_CAP (2)
class  MeasureModel:public QObject
{
    Q_OBJECT
public:
    MeasureModel(QObject *parent=nullptr);
    ~MeasureModel();
public:
    void setMeasureType(int type);
    int  getMeasureType(void);
    void startMeasure(void);
    void stopMeasure(void);
    void initMeasureCap(void);
public slots:
    void updateResMeasureValue(int val);
    void updateCapMeasureValue(int val);
private:
    int measureType;
    uint32_t resMeasureData;
    uint32_t capMeasureData;

    QThread *m_Thread;
    ResModel *resModel;
    CapModel *capModel;
signals:
    void showResMeasureText(QString text);
    void showCapMeasureText(QString text);
};

#endif // RESCAPMEASUREMENTMODEL_H
