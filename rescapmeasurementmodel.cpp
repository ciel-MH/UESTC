#include "rescapmeasurementmodel.h"
#include <QDebug>
#include <QObject>
#include <windows.h>
#include <QMessageBox>
extern HANDLE hCom1;
MeasureModel::MeasureModel(QObject *parent):QObject(parent)
{
    measureType=1;
    m_Thread=nullptr;
    resModel=nullptr;
    capModel=nullptr;
    resMeasureData=0;
    capMeasureData=0;
}

MeasureModel::~MeasureModel()
{

}

void MeasureModel::setMeasureType(int type)
{
    measureType=type;
}

int MeasureModel::getMeasureType()
{
    return measureType;
}

void MeasureModel::startMeasure()
{
    m_Thread=new QThread;
    qDebug() <<  "---debug-1------";
    if( 1 == measureType ){
        resModel=new ResModel;
        qDebug() << "---debug--2-----";
        resModel->moveToThread(m_Thread);
        connect(m_Thread,&QThread::finished,m_Thread,&QThread::deleteLater);
        connect(m_Thread,&QThread::started,resModel,&ResModel::startThreadSlot);
        connect(resModel,&ResModel::finishedMeasure,this,&MeasureModel::updateResMeasureValue);
        m_Thread->start();
    }else if(2 == measureType){
        capModel=new CapModel;
        qDebug() << "---debug--3-----";
        capModel->moveToThread(m_Thread);
        connect(m_Thread,&QThread::finished,m_Thread,&QThread::deleteLater);
        connect(m_Thread,&QThread::started,capModel,&CapModel::startThreadSlot);
        connect(capModel,&CapModel::finishedMeasure,this,&MeasureModel::updateCapMeasureValue);
        m_Thread->start();
    }
}

void MeasureModel::stopMeasure()
{
    if(1 == measureType){
        if(m_Thread->isRunning()){
            resModel->closeThread();
            m_Thread->quit();
            m_Thread->wait();
        }
    }else if(2 == measureType){
        if(m_Thread->isRunning()){
            capModel->closeThread();
            m_Thread->quit();
            m_Thread->wait();
        }
    }
}

void MeasureModel::initMeasureCap()
{
    DWORD writeSize;
    uint8_t Data[8]={0xAB,0x01,0xA1,0x00,0x00,0x00,0x01,0xBA};
    WriteFile(hCom1,Data,8,&writeSize,NULL);
    QThread::msleep(2000);
    WriteFile(hCom1,Data,8,&writeSize,NULL);
    QThread::msleep(2000);
    WriteFile(hCom1,Data,8,&writeSize,NULL);
    QThread::msleep(2000);
    QMessageBox::about(NULL,"提示","初始化完成");
}

void MeasureModel::updateResMeasureValue(int val)
{
    uint8_t gear=0;
    QString valueText;
    if(val < 6000){
       gear=2;
    }else if(val < 60000){
       gear=3;
    }else if(val < 600000){
        gear=4;
    }else if(val < 6000000){
        gear=5;
    }else if(val < 60000000){
        gear=6;
    }else if(val < 600000000){
        gear=7;
    }else{
        valueText=QString("ERROR!");
    }

    switch (gear){
    case 0x02:
        valueText=QString::number(val/10.0+0.01)+QString("Ω");
        break;
    case 0x03:
        valueText=QString::number(val/10000.0)+QString("KΩ");
        break;
    case 0x04:
        valueText=QString::number(val/10000.0)+QString("KΩ");
        break;
    case 0x05:
        valueText=QString::number(val/10000.0)+QString("KΩ");
        break;
    case 0x06:
        valueText=QString::number(val/10000000.0)+QString("MΩ");
        break;
    case 0x07:
       valueText=QString::number(val/10000000.0)+QString("MΩ");
        break;
    default:
        break;
    }
    resMeasureData=val;
    qDebug() << valueText;
    emit showResMeasureText(valueText);
}

void MeasureModel::updateCapMeasureValue(int val)
{
    capMeasureData=val;
    QString valueText;
    valueText=QString::number(val/1000.0)+QString("pF");
    emit showCapMeasureText(valueText);
}

