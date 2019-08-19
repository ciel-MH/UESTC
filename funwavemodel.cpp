#include "funwavemodel.h"
#include <QDebug>
#include <QThread>
#include <windows.h>
extern HANDLE hCom1;
extern bool WorkModelNorCal;
FunWaveModel::FunWaveModel()
{
    m_WaveType=FUNWAVE_FUN;
    m_WaveNo=1;
    m_SignalChannelOhm=HIGH_OHM;
    m_Amp.Unit=QString("Vpk-pk");
    m_Amp.Value=0;
    m_Frequence.Unit=QString("kHz");
    m_Frequence.Value=0;
}

FunWaveModel::~FunWaveModel()
{

}

bool FunWaveModel::SetWaveNo(uint8_t waveIndex)
{
    m_WaveNo=waveIndex;
    return true;
}

int FunWaveModel::GetWaveNo()
{
    return m_WaveNo;
}

void FunWaveModel::InitWaveNo(uint8_t waveIndex)
{
    m_WaveNo=waveIndex;
    m_SignalChannelOhm=LOW_OHM;
    m_Amp.Unit=QString("Vpk-pk");
    m_Amp.Value=20;
    m_Frequence.Unit=QString("kHz");
    m_Frequence.Value=1;
   // WaveParaSend();
}

bool FunWaveModel::WaveParaSend()
{
    DWORD writeSize;
    QByteArray waveNoControlWord;
    waveNoControlWord[0]=0xAB;
    waveNoControlWord[1]=0x01;
    waveNoControlWord[2]=0x61;
    waveNoControlWord[3]=0;
    waveNoControlWord[4]=0;
    waveNoControlWord[5]=0;
    waveNoControlWord[6]=0x01;
    waveNoControlWord[7]=0xBA;
    QByteArray OhmControlWord;
    OhmControlWord[0]=0xAB;
    OhmControlWord[1]=0x01;
    OhmControlWord[2]=0x64;
    OhmControlWord[3]=0;
    OhmControlWord[4]=0;
    OhmControlWord[5]=0;
    OhmControlWord[6]=0x01;
    OhmControlWord[7]=0xBA;
    QByteArray gearControlWord;
    gearControlWord[0]=0xAB;
    gearControlWord[1]=0x01;
    gearControlWord[2]=0x65;
    gearControlWord[3]=0;
    gearControlWord[4]=0;
    gearControlWord[5]=0;
    gearControlWord[6]=0x01;
    gearControlWord[7]=0xBA;
    switch (m_WaveNo) {
    case 1:
        waveNoControlWord[5]=1;
        qDebug() << "切换到正方波";
        break;
    case 2:
         waveNoControlWord[5]=2;
        qDebug() << "切换到负方波";
        break;
    case 3:
         waveNoControlWord[5]=3;
        qDebug() << "切换到对称方波";
        break;
    default:
        break;
    }
    switch (m_SignalChannelOhm) {
        case LOW_OHM:
            OhmControlWord[5]=2;
            qDebug() << "切换到50欧阻抗";
            break;
        case HIGH_OHM:
            OhmControlWord[5]=1;
            qDebug() << "切换到1M阻抗";
            break;
        default:
            break;
    }
    uint64_t word=GetAmpValue(m_Amp);
    if(word < 180000){
        gearControlWord[5]=1;
    }
    else if(word < 10000000){
        gearControlWord[5]=2;
    }else if(word < 8000000){
        gearControlWord[5]=3;
    }else if(word < 35000000){
        gearControlWord[5]=4;
    }else if(word < 150000000){
        gearControlWord[5]=5;
    }
    uint32_t sendword=0;
    sendword=AmpFreqConverToControlWord(word);

    QByteArray AmpControlWord;
    AmpControlWord[0]=0xAB;
    AmpControlWord[1]=0x01;
    AmpControlWord[2]=0x62;
    AmpControlWord[3]=(sendword >> 16) & 0xff;
    AmpControlWord[4]=(sendword >> 8 ) & 0xff;
    AmpControlWord[5]=(sendword) & 0xff;
    AmpControlWord[6]=0x01;
    AmpControlWord[7]=0xBA;
    qDebug() << AmpControlWord;
     WriteFile(hCom1,AmpControlWord,8,&writeSize,NULL);
     QThread::msleep(50);
    word=(uint64_t)(GetFreqValue(m_Frequence));
    sendword=AmpFreqConverToControlWord(word);
    QByteArray FreqControlWord;
    FreqControlWord[0]=0xAB;
    FreqControlWord[1]=0x01;
    FreqControlWord[2]=0x63;
    FreqControlWord[3]=(sendword >> 16) & 0xff;
    FreqControlWord[4]=(sendword >> 8 ) & 0xff;
    FreqControlWord[5]=(sendword) & 0xff;
    FreqControlWord[6]=0x01;
    FreqControlWord[7]=0xBA;
    WriteFile(hCom1,FreqControlWord,8,&writeSize,NULL);
    QThread::msleep(50);
    WriteFile(hCom1,waveNoControlWord,8,&writeSize,NULL);
     QThread::msleep(50);
    WriteFile(hCom1,OhmControlWord,8,&writeSize,NULL);
     QThread::msleep(50);
   // port.write(gearControlWord);
    qDebug() << FreqControlWord;
    QByteArray OutControlWord;
    if(WorkModelNorCal){
        OutControlWord[0]=0xAB;
        OutControlWord[1]=0x01;
        OutControlWord[2]=0x65;
        OutControlWord[3]=0;
        OutControlWord[4]=0;
        OutControlWord[5]=0;
        OutControlWord[6]=0x01;
        OutControlWord[7]=0xBA;
    }else{
        OutControlWord[0]=0xAB;
        OutControlWord[1]=0x02;
        OutControlWord[2]=0x66;
        OutControlWord[3]=0;
        OutControlWord[4]=0;
        OutControlWord[5]=0;
        OutControlWord[6]=0x02;
        OutControlWord[7]=0xBA;
    }
    WriteFile(hCom1,OutControlWord,8,&writeSize,NULL);

    qDebug() << "幅值：" << m_Amp.Value << m_Amp.Unit;
    qDebug() << "频率:" << m_Frequence.Value << m_Frequence.Unit;
    return true;
}

void FunWaveModel::WaveInit()
{
    InitWaveNo(FUNWAVE_SIN);
    return;
}

bool FunWaveModel::SetSignalChannelOhm(int ohm)
{
    m_SignalChannelOhm=ohm;
    return true;
}

int FunWaveModel::GetSignalChannelOhm()
{
    return m_SignalChannelOhm;
}

bool FunWaveModel::SetFrequencePara(Para freq)
{
    m_Frequence=freq;
    return true;
}

Para FunWaveModel::GetFrequencePara()
{
    return m_Frequence;
}

void FunWaveModel::SetWaveAmp(Para val)
{
    m_Amp=val;
    return;
}

Para FunWaveModel::GetWaveAmp()
{
    return m_Amp;
}

void FunWaveModel::Open()
{
    qDebug() << "打开函数波模块" << endl;
}

void FunWaveModel::Close()
{
    DWORD writeSize;
    uint8_t Data[8]={0xAB,0x01,0x66,0x00,0x00,0x00,0x01,0xBA};
    WriteFile(hCom1,Data,8,&writeSize,NULL);
    qDebug() << "关闭函数波模块" << endl;

}
