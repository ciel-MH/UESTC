#include "sinmodel.h"
#include <QDebug>
#include <QSerialPort>
#include <windows.h>
extern HANDLE hCom1;
extern bool WorkModelNorCal;
SinModel::SinModel()
{
    m_WaveType=SINUSOID_FUN;
    m_WaveNo=SINGLECHANNEL;
    m_SignalChannelOhm=LOW_OHM;
    m_Amp.Unit=QString("mVpk-pk");
    m_Amp.Value=0;
    m_Frequence.Unit=QString("kHz");
    m_Frequence.Value=0;
}

SinModel::~SinModel()
{

}

bool SinModel::SetWaveNo(uint8_t waveIndex)
{
    m_WaveNo=waveIndex;
    return true;
}

int SinModel::GetWaveNo()
{
    return m_WaveNo;
}

void SinModel::InitWaveNo(uint8_t waveIndex)
{
    m_WaveNo=waveIndex;
    m_SignalChannelOhm=LOW_OHM;
    m_Amp.Unit=QString("mVpk-pk");
    m_Amp.Value=20;
    m_Frequence.Unit=QString("kHz");
    m_Frequence.Value=1;
    WaveParaSend();
}

bool SinModel::WaveParaSend()
{
    qDebug() << "发送" << m_Frequence.Value << m_Frequence.Unit << "频率";
    qDebug() << "发送" << m_Amp.Value << m_Amp.Unit << "幅值";
    DWORD writeSize;
        uint64_t word=GetAmpValue(m_Amp);
        uint32_t sendword=0;
        sendword=AmpFreqConverToControlWord(word);
        QByteArray AmpControlWord;
        AmpControlWord[0]=0xAB;
        AmpControlWord[1]=0x01;
        AmpControlWord[2]=0x41;
        AmpControlWord[3]=(sendword >> 16) & 0xff;
        AmpControlWord[4]=(sendword >> 8 ) & 0xff;
        AmpControlWord[5]=(sendword) & 0xff;
        AmpControlWord[6]=0x01;
        AmpControlWord[7]=0xBA;
        qDebug() << AmpControlWord;
        WriteFile(hCom1,AmpControlWord,8,&writeSize,NULL);

        word=(uint64_t)(GetFreqValue(m_Frequence));
        sendword=AmpFreqConverToControlWord(word);
        QByteArray FreqControlWord;
        FreqControlWord[0]=0xAB;
        FreqControlWord[1]=0x01;
        FreqControlWord[2]=0x42;
        FreqControlWord[3]=(sendword >> 16) & 0xff;
        FreqControlWord[4]=(sendword >> 8 ) & 0xff;
        FreqControlWord[5]=(sendword) & 0xff;
        FreqControlWord[6]=0x01;
        FreqControlWord[7]=0xBA;
         WriteFile(hCom1,FreqControlWord,8,&writeSize,NULL);
        qDebug() << FreqControlWord;

        QByteArray OutControlWord;
        if(WorkModelNorCal){
            OutControlWord[0]=0xAB;
            OutControlWord[1]=0x01;
            OutControlWord[2]=0x43;
            OutControlWord[3]=0;
            OutControlWord[4]=0;
            OutControlWord[5]=0;
            OutControlWord[6]=0x01;
            OutControlWord[7]=0xBA;
        }else{
            OutControlWord[0]=0xAB;
            OutControlWord[1]=0x02;
            OutControlWord[2]=0x44;
            OutControlWord[3]=0;
            OutControlWord[4]=0;
            OutControlWord[5]=0;
            OutControlWord[6]=0x02;
            OutControlWord[7]=0xBA;
        }
        WriteFile(hCom1,OutControlWord,8,&writeSize,NULL);
    return true;
}

void SinModel::WaveInit()
{
    InitWaveNo(POSITIVE_SQUARE);
    return;
}

bool SinModel::SetSignalChannelOhm(int ohm)
{
    m_SignalChannelOhm=ohm;
    return true;
}

int SinModel::GetSignalChannelOhm()
{
    return m_SignalChannelOhm;
}

bool SinModel::SetFrequencePara(Para para)
{
    m_Frequence=para;
    return true;
}

Para SinModel::GetFrequencePara()
{
    return m_Frequence;
}

void SinModel::SetWaveAmp(Para val)
{
    m_Amp=val;
    return;
}

Para SinModel::GetWaveAmp()
{
    return m_Amp;
}

void SinModel::Open()
{
    qDebug() << "打开正弦模块";
}

void SinModel::Close()
{
    DWORD writeSize;
    QByteArray AmpControlWord;
    AmpControlWord[0]=0xAB;
    AmpControlWord[1]=0x01;
    AmpControlWord[2]=0x44;
    AmpControlWord[3]=0;
    AmpControlWord[4]=0;
    AmpControlWord[5]=0;
    AmpControlWord[6]=0x01;
    AmpControlWord[7]=0xBA;
    qDebug() << AmpControlWord;
    WriteFile(hCom1,AmpControlWord,8,&writeSize,NULL);
    qDebug() << "关闭正弦模块";
}
