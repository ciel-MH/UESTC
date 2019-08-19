#include "pulsewidthmodel.h"
#include <QSerialPort>
#include <QMessageBox>
#include <QThread>
#include <windows.h>
extern HANDLE hCom1;
extern QSerialPort port;
extern bool WorkModelNorCal;
PulseWidthModel::PulseWidthModel()
{
    m_WaveType=PWIDTH_FUN;
    m_WaveNo=PULSE_WIDTH;
    m_SignalChannelOhm=LOW_OHM;
    m_Amp.Unit=QString("uVpk-pk");
    m_Amp.Value=0;
    m_Frequence.Unit=QString("Hz");
    m_Frequence.Value=0;
    m_PulsePeriodPara.Unit=QString("ns");
    m_PulsePeriodPara.Value=0;
}

PulseWidthModel::~PulseWidthModel()
{

}

bool PulseWidthModel::SetWaveNo(uint8_t waveIndex)
{
    m_WaveNo=waveIndex;
    return true;
}

int PulseWidthModel::GetWaveNo()
{
    return m_WaveNo;
}

void PulseWidthModel::InitWaveNo(uint8_t waveIndex)
{
    m_WaveNo=waveIndex;
    m_Amp.Unit=QString("V");
    m_Amp.Value=1;
    m_Frequence.Unit=QString("kHz");
    m_Frequence.Value=1;
    m_PulsePeriodPara.Unit=QString("ns");
    m_PulsePeriodPara.Value=20;
    WaveParaSend();
}

bool PulseWidthModel::WaveParaSend()
{
    DWORD writeSize;
    qDebug() << "发送脉宽 " << m_PulsePeriodPara.Value << m_PulsePeriodPara.Unit;
    uint64_t word=(uint64_t)(GetAmpValue(m_Amp));
    uint32_t controlword=0;
    controlword=AmpFreqConverToControlWord(word);
    QByteArray AmpControlWord;
    AmpControlWord[0]=0xAB;
    AmpControlWord[1]=0x02;
    AmpControlWord[2]=0x71;
    AmpControlWord[3]=(controlword >> 16) & 0xff;
    AmpControlWord[4]=(controlword >> 8 ) & 0xff;
    AmpControlWord[5]=(controlword) & 0xff;
    AmpControlWord[6]=0x01;
    AmpControlWord[7]=0xBA;
    qDebug() << AmpControlWord;

    word=(uint64_t)(GetFreqValue(m_Frequence));
    controlword=AmpFreqConverToControlWord(word);
    QByteArray FreqControlWord;
    FreqControlWord[0]=0xAB;
    FreqControlWord[1]=0x01;
    FreqControlWord[2]=0x72;
    FreqControlWord[3]=(controlword >> 16) & 0xff;
    FreqControlWord[4]=(controlword >> 8 ) & 0xff;
    FreqControlWord[5]=(controlword) & 0xff;
    FreqControlWord[6]=0x01;
    FreqControlWord[7]=0xBA;

    word=GetPeriodParaValue(m_PulsePeriodPara);
    controlword=AmpFreqConverToControlWord(word);
    QByteArray PeriodControlWord;
    PeriodControlWord[0]=0xAB;
    PeriodControlWord[1]=0x01;
    PeriodControlWord[2]=0x73;
    PeriodControlWord[3]=(controlword >> 16) & 0xff;
    PeriodControlWord[4]=(controlword >> 8 ) & 0xff;
    PeriodControlWord[5]=(controlword) & 0xff;
    PeriodControlWord[6]=0x01;
    PeriodControlWord[7]=0xBA;

    QByteArray OutControlWord;
    OutControlWord[0]=0xAB;
    OutControlWord[1]=0x01;
    OutControlWord[2]=0x74;
    OutControlWord[3]=0;
    OutControlWord[4]=0;
    OutControlWord[5]=0;
    OutControlWord[6]=0x01;
    OutControlWord[7]=0xBA;
    WriteFile(hCom1,AmpControlWord,8,&writeSize,NULL);
    QThread::msleep(50);
    WriteFile(hCom1,FreqControlWord,8,&writeSize,NULL);

    QThread::msleep(50);
    WriteFile(hCom1,PeriodControlWord,8,&writeSize,NULL);

    QThread::msleep(50);
    WriteFile(hCom1,OutControlWord,8,&writeSize,NULL);

    return true;
}

void PulseWidthModel::WaveInit()
{
    InitWaveNo(PULSE_WIDTH);
    return;
}

bool PulseWidthModel::SetSignalChannelOhm(int ohm)
{
    m_SignalChannelOhm=ohm;
    return true;
}

int PulseWidthModel::GetSignalChannelOhm()
{
    return m_SignalChannelOhm;
}

bool PulseWidthModel::SetFrequencePara(Para freq)
{
    m_Frequence=freq;
    return true;
}

Para PulseWidthModel::GetFrequencePara()
{
    return m_Frequence;
}

void PulseWidthModel::SetWaveAmp(Para val)
{
    m_Amp=val;
    return;
}

Para PulseWidthModel::GetWaveAmp()
{
    return m_Amp;
}

void PulseWidthModel::Open()
{
    qDebug() << "打开可调脉宽模块";
}

void PulseWidthModel::Close()
{
    DWORD writeSize;
    uint8_t Data[8]={0xAB,0x01,0x75,0x00,0x00,0x00,0x01,0xBA};
    WriteFile(hCom1,Data,8,&writeSize,NULL);
    qDebug() << "关闭可调脉宽模块";
}

bool PulseWidthModel::SetPulsePeriodPara(Para val)
{
    m_PulsePeriodPara=val;
    return true;
}

Para PulseWidthModel::GetPulsePeriodPara(void)
{
    return m_PulsePeriodPara;
}
