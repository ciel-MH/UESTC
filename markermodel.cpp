#include "markermodel.h"
#include <QSerialPort>
#include <windows.h>
#include <QThread>
extern HANDLE hCom1;
extern bool WorkModelNorCal;
MarkerModel::MarkerModel()
{
    m_WaveType=MARKER_FUN;
    m_WaveNo=MARKER_SQUARE;
    m_SignalChannelOhm=LOW_OHM;
    m_Amp.Unit=QString("V");
    m_Amp.Value=0;
    m_Frequence.Unit=QString("kHz");
    m_Frequence.Value=0;
}

MarkerModel::~MarkerModel()
{

}

bool MarkerModel::SetWaveNo(uint8_t waveIndex)
{
    m_WaveNo=waveIndex;
    return true;
}

int MarkerModel::GetWaveNo()
{
    return m_WaveNo;
}

void MarkerModel::InitWaveNo(uint8_t waveIndex)
{
    m_WaveNo=waveIndex;
    m_SignalChannelOhm=LOW_OHM;
    m_Amp.Unit=QString("Vpk-pk");
    m_Amp.Value=1;
    m_Frequence.Unit=QString("kHz");
    m_Frequence.Value=1;
    WaveParaSend();
    return;
}

bool MarkerModel::WaveParaSend()
{
    PeriodParaToFrePara();
    DWORD writeSize;
    uint64_t word=GetAmpValue(m_Amp);
    QByteArray waveNoControlWord;
    waveNoControlWord[0]=0xAB;
    waveNoControlWord[1]=0x01;
    waveNoControlWord[2]=0x51;
    waveNoControlWord[3]=0x0;
    waveNoControlWord[4]=0x0;
    waveNoControlWord[5]=m_WaveNo;
    waveNoControlWord[6]=0x01;
    waveNoControlWord[7]=0xBA;

    WriteFile(hCom1,waveNoControlWord,8,&writeSize,NULL);
    QThread::msleep(50);
    uint32_t sendword=0;
    sendword=AmpFreqConverToControlWord(word);
    QByteArray AmpControlWord;
    AmpControlWord[0]=0xAB;
    AmpControlWord[1]=0x01;
    AmpControlWord[2]=0x53;
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
    FreqControlWord[2]=0x52;
    FreqControlWord[3]=(sendword >> 16) & 0xff;
    FreqControlWord[4]=(sendword >> 8 ) & 0xff;
    FreqControlWord[5]=(sendword) & 0xff;
    FreqControlWord[6]=0x01;
    FreqControlWord[7]=0xBA;
    WriteFile(hCom1,FreqControlWord,8,&writeSize,NULL);
     QThread::msleep(50);
    qDebug() << FreqControlWord;

    QByteArray OutControlWord;
    if(WorkModelNorCal){
        OutControlWord[0]=0xAB;
        OutControlWord[1]=0x01;
        OutControlWord[2]=0x54;
        OutControlWord[3]=0;
        OutControlWord[4]=0;
        OutControlWord[5]=0;
        OutControlWord[6]=0x01;
        OutControlWord[7]=0xBA;
    }else{
        OutControlWord[0]=0xAB;
        OutControlWord[1]=0x02;
        OutControlWord[2]=0x54;
        OutControlWord[3]=0;
        OutControlWord[4]=0;
        OutControlWord[5]=0;
        OutControlWord[6]=0x02;
        OutControlWord[7]=0xBA;
    }
    WriteFile(hCom1,OutControlWord,8,&writeSize,NULL);
    qDebug() << "幅值：" << m_Amp.Value << m_Amp.Unit;
    qDebug() << "频率:" << m_PeriodPara.Value << m_PeriodPara.Unit;
    return true;
}

void MarkerModel::WaveInit()
{
    InitWaveNo(MARKER_SQUARE);
    return;
}

bool MarkerModel::SetSignalChannelOhm(int ohm)
{
    m_SignalChannelOhm=ohm;
    return true;
}

int MarkerModel::GetSignalChannelOhm()
{
    return m_SignalChannelOhm;
}

bool MarkerModel::SetFrequencePara(Para Freq)
{
    m_Frequence=Freq;
    return true;
}

Para MarkerModel::GetFrequencePara()
{
    return m_Frequence;
}

void MarkerModel::SetWaveAmp(Para val)
{
    m_Amp=val;
    return;
}

Para MarkerModel::GetWaveAmp()
{
    return m_Amp;
}

bool MarkerModel::SetPeriodPara(Para para)
{
    m_PeriodPara=para;
    return true;
}

Para MarkerModel::GetPeriodPara()
{
    return m_PeriodPara;
}

void MarkerModel::Open()
{
    qDebug() << "打开时标模块";
}

void MarkerModel::Close()
{
    DWORD writeSize;
    uint8_t Data[8]={0xAB,0x01,0x55,0x00,0x00,0x00,0x01,0xBA};
    WriteFile(hCom1,Data,8,&writeSize,NULL);
    qDebug() << "关闭时标模块";
}

bool MarkerModel::FreParaToPeriodPara()
{
    if( m_Frequence.Unit == QString("Hz"))
    {
        m_PeriodPara.Unit=QString("s");
        m_PeriodPara.Value=1.0/m_Frequence.Value;
    }
    else if (m_Frequence.Unit == QString("kHz"))
    {
        m_PeriodPara.Unit=QString("ms");
        m_PeriodPara.Value=1.0/m_Frequence.Value;
    }
    else if(m_Frequence.Unit == QString("MHz"))
    {
        m_PeriodPara.Unit=QString("us");
        m_PeriodPara.Value=1.0/m_Frequence.Value;
    }
    else if(m_Frequence.Unit == QString("GHz"))
    {
        m_PeriodPara.Unit=QString("ns");
        m_PeriodPara.Value=1.0/m_Frequence.Value;
    }
    PeriodValueAndUnitProcess(m_PeriodPara);
    return true;
}

bool MarkerModel::PeriodParaToFrePara()
{
    if ( m_PeriodPara.Unit == QString("s"))
        {
            m_Frequence.Unit=QString("Hz");
            m_Frequence.Value=1.0/m_PeriodPara.Value;
        }
        else if (m_PeriodPara.Unit == QString("ms"))
        {
            m_Frequence.Unit=QString("kHz");
            m_Frequence.Value=1.0/m_PeriodPara.Value;
        }
        else if(m_PeriodPara.Unit == QString("us"))
        {
            m_Frequence.Unit=QString("MHz");
            m_Frequence.Value=1.0/m_PeriodPara.Value;
        }
        else if(m_PeriodPara.Unit == QString("ns"))
        {
            m_Frequence.Unit=QString("GHz");
            m_Frequence.Value=1.0/m_PeriodPara.Value;
        }
        FrequencyValueAndUnitProcess(m_Frequence);
        return true;
}
