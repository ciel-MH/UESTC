#include "overloadpulsemodel.h"
#include <windows.h>
#include <QThread>
extern HANDLE hCom1;
extern bool WorkModelNorCal;
OverloadPulseModel::OverloadPulseModel()
{
    m_WaveType=OVERLOADPULSE_FUN;
    m_WaveNo=OVERLOAD_PULSE;
    m_SignalChannelOhm=LOW_OHM;
    m_Amp.Unit=QString("Vpk-pk");
    m_Amp.Value=0;
    m_DurationPara.Unit=QString("s");
    m_DurationPara.Value=0;
    m_EnergyPara.Unit=QString("J");
    m_EnergyPara.Value=0;
}

OverloadPulseModel::~OverloadPulseModel()
{

}

bool OverloadPulseModel::SetWaveNo(uint8_t waveIndex)
{
    m_WaveNo=waveIndex;
    return true;
}

int OverloadPulseModel::GetWaveNo()
{
    return m_WaveNo;
}

void OverloadPulseModel::InitWaveNo(uint8_t waveIndex)
{
    /*
    m_WaveNo=waveIndex;
    m_SignalChannelOhm=LOW_OHM;
    m_Amp.Unit=QString("Vpk-pk");
    m_Amp.Value=20;
    m_DurationPara.Unit=QString("s");
    m_DurationPara.Value=0.2;
    m_EnergyPara.Unit=QString("J");
    m_EnergyPara.Value=1.6;
    WaveParaSend();
    */
    return;
}

bool OverloadPulseModel::WaveParaSend()
{
    DWORD writeSize;
    qDebug() << "发送幅值：" << m_Amp.Value << m_Amp.Unit;
    uint64_t word=GetAmpValue(m_Amp);
    uint32_t sendword=0;
    sendword=AmpFreqConverToControlWord(word);
    QByteArray AmpControlWord;
    AmpControlWord[0]=0xAB;
    AmpControlWord[1]=0x01;
    AmpControlWord[2]=0xB1;
    AmpControlWord[3]=(sendword >> 16) & 0xff;
    AmpControlWord[4]=(sendword >> 8 ) & 0xff;
    AmpControlWord[5]=(sendword) & 0xff;
    AmpControlWord[6]=0x01;
    AmpControlWord[7]=0xBA;
    qDebug() << AmpControlWord;
    WriteFile(hCom1,AmpControlWord,8,&writeSize,NULL);
    qDebug() << "发送时长: " << m_DurationPara.Value << m_DurationPara.Unit;
    QThread::msleep(50);
    word=m_DurationPara.Value*1000000;
    sendword=AmpFreqConverToControlWord(word);
    QByteArray PeriodControlWord;
    PeriodControlWord[0]=0xAB;
    PeriodControlWord[1]=0x01;
    PeriodControlWord[2]=0xB2;
    PeriodControlWord[3]=(sendword >> 16) & 0xff;
    PeriodControlWord[4]=(sendword >> 8 ) & 0xff;
    PeriodControlWord[5]=(sendword) & 0xff;
    PeriodControlWord[6]=0x01;
    PeriodControlWord[7]=0xBA;
    WriteFile(hCom1,PeriodControlWord,8,&writeSize,NULL);
    QThread::msleep(50);
    QByteArray OutControlWord;
    OutControlWord[0]=0xAB;
    OutControlWord[1]=0x01;
    OutControlWord[2]=0xB3;
    OutControlWord[3]=0;
    OutControlWord[4]=0;
    OutControlWord[5]=0;
    OutControlWord[6]=0x01;
    OutControlWord[7]=0xBA;
    WriteFile(hCom1,OutControlWord,8,&writeSize,NULL);
    return true;
}

void OverloadPulseModel::WaveInit()
{
    InitWaveNo(OVERLOAD_PULSE);
    return;
}

bool OverloadPulseModel::SetSignalChannelOhm(int ohm)
{
    m_SignalChannelOhm=ohm;
    return true;
}

int OverloadPulseModel::GetSignalChannelOhm()
{
    return m_SignalChannelOhm;
}

void OverloadPulseModel::SetWaveAmp(Para val)
{
    m_Amp=val;
    return;
}

Para OverloadPulseModel::GetWaveAmp()
{
    return m_Amp;
}

void OverloadPulseModel::SetEnergePara(Para val)
{
    m_EnergyPara=val;
    return;
}

Para OverloadPulseModel::GetEnergePara()
{
    return m_EnergyPara;
}

void OverloadPulseModel::SetPowerPara(Para val)
{
    m_PowerPara=val;
    return;
}

Para OverloadPulseModel::GetPowerPara()
{
    return m_PowerPara;
}

void OverloadPulseModel::SetDurationPara(Para val)
{
    m_DurationPara=val;
    return;
}

Para OverloadPulseModel::GetDurationPara()
{
    return m_DurationPara;
}

void OverloadPulseModel::Open()
{
    qDebug() << "打开过载脉冲模块";
}

void OverloadPulseModel::Close()
{
    qDebug() << "关闭过载脉冲模块";
}
