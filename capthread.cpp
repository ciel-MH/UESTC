#include "capthread.h"
#include <QDebug>
#include <QMessageBox>
#include <windows.h>
extern HANDLE hCom1;
extern bool WorkModelNorCal;
CapModel::CapModel(QObject *parent):QObject(parent)
{
    isStop=false;
}

void CapModel::closeThread()
{
    mutex.lock();
    isStop=true;
    mutex.unlock();
}

void CapModel::startThreadSlot()
{
    mutex.lock();
    isStop=false;
    mutex.unlock();
    uint8_t CapControlWord[8]={0};
    if(WorkModelNorCal){
    CapControlWord[0]=0xAB;
    CapControlWord[1]=0x01;
    CapControlWord[2]=0xA2;
    CapControlWord[3]=0;
    CapControlWord[4]=0;
    CapControlWord[5]=0;
    CapControlWord[6]=0x01;
    CapControlWord[7]=0xBA;
    }
    else{
        CapControlWord[0]=0xAB;
        CapControlWord[1]=0x02;
        CapControlWord[2]=0xA2;
        CapControlWord[3]=0;
        CapControlWord[4]=0;
        CapControlWord[5]=0;
        CapControlWord[6]=0x02;
        CapControlWord[7]=0xBA;
    }
    uint8_t ReadData[4]={0};
    DWORD writeSize,readSize;
    int val=0;

    while(!isStop){
        WriteFile(hCom1,CapControlWord,8,&writeSize,NULL);
        QThread::msleep(1000);
        ReadFile(hCom1,ReadData,4,&readSize,NULL);

        val=(ReadData[0] << 24) | \
                  (ReadData[1] << 16) | \
                      (ReadData[2] << 8)  | \
                          (ReadData[3]);
        emit finishedMeasure(val);
        qDebug() << val;
        QThread::msleep(1000);
       /* val +=10;
        emit finishedMeasure(val);
        qDebug() << val;
        QThread::msleep(500);*/
    }
}
