#include "videotrigermodel.h"
#include <QThread>
#include <windows.h>
extern HANDLE hCom1;
VideoTrigerModel::VideoTrigerModel()
{
    m_Polarity=TV_POLARITY_POS;
    m_Sync=TV_SYNC_625;
    m_BrightLevel=TV_BRIGHTLEVEL_WHITE;
}

VideoTrigerModel::~VideoTrigerModel()
{

}

void VideoTrigerModel::SetPolarity(uint8_t polarity)
{
     m_Polarity=polarity;
}

void VideoTrigerModel::SetBrightLevel(uint8_t brightlevel)
{
    m_BrightLevel=brightlevel;
}

void VideoTrigerModel::SetSync(uint8_t sync)
{
    m_Sync=sync;
}

bool VideoTrigerModel::WaveParaSend()
{
    DWORD writeSize;
    QByteArray PolarityControlWord;
    PolarityControlWord[0]=0xAB;
    PolarityControlWord[1]=0x01;
    PolarityControlWord[2]=0x83;
    PolarityControlWord[3]=0x00;
    PolarityControlWord[4]=0x00;
    PolarityControlWord[5]=m_Polarity;
    PolarityControlWord[6]=0x01;
    PolarityControlWord[7]=0xBA;
    WriteFile(hCom1,PolarityControlWord,8,&writeSize,NULL);
    QThread::msleep(30);
    QByteArray BrightLevelControlWord;
    BrightLevelControlWord[0]=0xAB;
    BrightLevelControlWord[1]=0x01;
    BrightLevelControlWord[2]=0x81;
    BrightLevelControlWord[3]=0x00;
    BrightLevelControlWord[4]=0x00;
    BrightLevelControlWord[5]=m_BrightLevel;
    BrightLevelControlWord[6]=0x01;
    BrightLevelControlWord[7]=0xBA;
    WriteFile(hCom1,BrightLevelControlWord,8,&writeSize,NULL);
     QThread::msleep(30);
    QByteArray SyncControlWord;
    SyncControlWord[0]=0xAB;
    SyncControlWord[1]=0x01;
    SyncControlWord[2]=0x82;
    SyncControlWord[3]=0x00;
    SyncControlWord[4]=0x00;
    SyncControlWord[5]=m_Sync;
    SyncControlWord[6]=0x01;
    SyncControlWord[7]=0xBA;
    WriteFile(hCom1,SyncControlWord,8,&writeSize,NULL);
    QThread::msleep(30);
    QByteArray OutControlWord;
    OutControlWord[0]=0xAB;
    OutControlWord[1]=0x01;
    OutControlWord[2]=0x84;
    OutControlWord[3]=0x00;
    OutControlWord[4]=0x00;
    OutControlWord[5]=0x00;
    OutControlWord[6]=0x01;
    OutControlWord[7]=0xBA;
    WriteFile(hCom1,OutControlWord,8,&writeSize,NULL);
    return true;
}

void VideoTrigerModel::WaveInit()
{

}

void VideoTrigerModel::close()
{
    DWORD writeSize;
    QByteArray OutControlWord;
    OutControlWord[0]=0xAB;
    OutControlWord[1]=0x01;
    OutControlWord[2]=0x85;
    OutControlWord[3]=0x00;
    OutControlWord[4]=0x00;
    OutControlWord[5]=0x00;
    OutControlWord[6]=0x01;
    OutControlWord[7]=0xBA;
    WriteFile(hCom1,OutControlWord,8,&writeSize,NULL);
    QThread::msleep(30);
}
