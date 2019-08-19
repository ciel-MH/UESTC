#include "edgemodel.h"
#include <QDebug>
#include <QtSerialPort/qserialport.h>
#include <windows.h>
#include <QThread>
extern HANDLE hCom1;
extern bool WorkModelNorCal;
EdgeModel::EdgeModel()
{
    m_WaveType=EDGE_FUN;
    m_WaveNo=Edge_150ps;
    m_SignalChannelOhm=LOW_OHM;
    m_Amp.Unit=QString("mVpk-pk");
    m_Amp.Value=0;
    m_Frequence.Unit=QString("kHz");
    m_Frequence.Value=0;
    m_RisingFallingFlag=Edge_Rising;
}

EdgeModel::~EdgeModel()
{

}

bool EdgeModel::SetWaveNo(uint8_t waveIndex)
{
    m_WaveNo=waveIndex;
    return true;
}

int EdgeModel::GetWaveNo()
{
    return m_WaveNo;
}

void EdgeModel::InitWaveNo(uint8_t waveIndex)
{
    m_WaveNo=waveIndex;
    m_SignalChannelOhm=LOW_OHM;
    m_Amp.Unit=QString("mVpk-pk");
    m_Amp.Value=20;
    m_Frequence.Unit=QString("kHz");
    m_Frequence.Value=1;
    WaveParaSend();
}

bool EdgeModel::WaveParaSend()
{
    DWORD writeSize;
    switch (m_WaveNo) {
    case Edge_150ps:
        qDebug() << "切换到150ps";
        break;
    case Edge_500ps:
        qDebug() << "切换到500ps";
        break;
    default:
        break;
    }
    uint8_t edgeType[8]={0xAB,0x01,0x33,0,0,0,0x01,0xBA};
    if(m_RisingFallingFlag){
            qDebug() << "上升沿";
            edgeType[5]=1;
    }else{
        qDebug() << "下降沿";
        edgeType[5]=2;
    }
    WriteFile(hCom1,edgeType,8,&writeSize,NULL);

    qDebug() << "发送" << m_Frequence.Value << m_Frequence.Unit << "频率";
    uint64_t word=GetAmpValue(m_Amp);
    uint32_t sendword=0;
    sendword=AmpFreqConverToControlWord(word);
    QByteArray AmpControlWord;

    AmpControlWord[0]=0xAB;
    AmpControlWord[1]=0x01;
    AmpControlWord[2]=0x31;
    AmpControlWord[3]=(sendword >> 16) & 0xff;
    AmpControlWord[4]=(sendword >> 8 ) & 0xff;
    AmpControlWord[5]=(sendword) & 0xff;
    AmpControlWord[6]=0x01;
    AmpControlWord[7]=0xBA;
    qDebug() << "Edge_Amp_Word: " << AmpControlWord;
    WriteFile(hCom1,AmpControlWord,8,&writeSize,NULL);

    word=(uint64_t)(GetFreqValue(m_Frequence));
    sendword=AmpFreqConverToControlWord(word);
    QByteArray FreqControlWord;
    FreqControlWord[0]=0xAB;
    FreqControlWord[1]=0x01;
    FreqControlWord[2]=0x32;
    FreqControlWord[3]=(sendword >> 16) & 0xff;
    FreqControlWord[4]=(sendword >> 8 ) & 0xff;
    FreqControlWord[5]=(sendword) & 0xff;
    FreqControlWord[6]=0x01;
    FreqControlWord[7]=0xBA;
    WriteFile(hCom1,FreqControlWord,8,&writeSize,NULL);
    qDebug() << "Edge_Freq_Word: " << FreqControlWord;
    QByteArray OutControlWord;
    if(WorkModelNorCal){
        OutControlWord[0]=0xAB;
        OutControlWord[1]=0x01;
        OutControlWord[2]=0x34;
        OutControlWord[3]=0;
        OutControlWord[4]=0;
        OutControlWord[5]=0;
        OutControlWord[6]=0x01;
        OutControlWord[7]=0xBA;
    }else{
        OutControlWord[0]=0xAB;
        OutControlWord[1]=0x02;
        OutControlWord[2]=0x34;
        OutControlWord[3]=0;
        OutControlWord[4]=0;
        OutControlWord[5]=0;
        OutControlWord[6]=0x02;
        OutControlWord[7]=0xBA;
    }
    WriteFile(hCom1,OutControlWord,8,&writeSize,NULL);
    qDebug() << OutControlWord;
    qDebug() << "发送" << m_Amp.Value << m_Amp.Unit << "幅值";
    return true;
}

void EdgeModel::WaveInit()
{
    InitWaveNo(Edge_500ps);
    return;
}

bool EdgeModel::SetSignalChannelOhm(int ohm)
{
    m_SignalChannelOhm=ohm;
    return true;
}

int EdgeModel::GetSignalChannelOhm()
{
    return m_SignalChannelOhm;
}

bool EdgeModel::SetFrequencePara(Para Freq)
{
    m_Frequence=Freq;
    return true;
}

Para EdgeModel::GetFrequencePara()
{
    return m_Frequence;
}

void EdgeModel::SetRisingFallingFlag(bool flag)
{
    m_RisingFallingFlag=flag;
}

bool EdgeModel::GetRisingFallingFlag()
{
    return m_RisingFallingFlag;
}

void EdgeModel::SetWaveAmp(Para val)
{
    m_Amp=val;
    return;
}

Para EdgeModel::GetWaveAmp()
{
    return m_Amp;
}

void EdgeModel::Open()
{
    qDebug() << "打开快沿模块";
}

void EdgeModel::Close()
{
    DWORD writeSize;
    uint8_t Data[8]={0xAB,0x01,0x35,0x00,0x00,0x00,0x01,0xBA};
    WriteFile(hCom1,Data,8,&writeSize,NULL);
   // QThread::msleep(50);
    qDebug() << "关闭快沿模块";
}
