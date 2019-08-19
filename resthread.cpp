#include "resthread.h"

#include <QDebug>
#include <windows.h>
extern HANDLE hCom1;
extern bool WorkModelNorCal;
ResModel::ResModel(QObject *parent):QObject(parent)
{
    isStop=false;
}

void ResModel::closeThread()
{
    mutex.lock();
    isStop=true;
    mutex.unlock();
}

void ResModel::startThreadSlot()
{
    mutex.lock();
    isStop=false;
    mutex.unlock();

    unsigned char ResControlWord[8]={0};
    unsigned char ResInitControlWord[8]={0};
    unsigned char RevData[4]={0};
    ResInitControlWord[0]=0xAB;
    ResInitControlWord[1]=0x01;
    ResInitControlWord[2]=0x91;
    ResInitControlWord[3]=0;
    ResInitControlWord[4]=0;
    ResInitControlWord[5]=0;
    ResInitControlWord[6]=0x01;
    ResInitControlWord[7]=0xBA;
    if(WorkModelNorCal){
    ResControlWord[0]=0xAB;
    ResControlWord[1]=0x01;
    ResControlWord[2]=0x92;
    ResControlWord[3]=0;
    ResControlWord[4]=0;
    ResControlWord[5]=0;
    ResControlWord[6]=0x01;
    ResControlWord[7]=0xBA;
    }else{
        ResControlWord[0]=0xAB;
        ResControlWord[1]=0x02;
        ResControlWord[2]=0x92;
        ResControlWord[3]=0;
        ResControlWord[4]=0;
        ResControlWord[5]=0;
        ResControlWord[6]=0x02;
        ResControlWord[7]=0xBA;
    }
    DWORD writeSize,readSize;
    WriteFile(hCom1,ResInitControlWord,8,&writeSize,NULL);
    QThread::msleep(4000);

    int val=0;
    while(!isStop){
       WriteFile(hCom1,ResControlWord,8,&writeSize,NULL);
       QThread::msleep(500);
       ReadFile(hCom1,RevData,4,&readSize,NULL);

      // val +=10;
       val=(RevData[0] << 24) | \
                (RevData[1] << 16) | \
                    (RevData[2] << 8)  | \
                        (RevData[3] );
       emit finishedMeasure(val);
       qDebug() << val;
       QThread::msleep(1000);
    }
}
