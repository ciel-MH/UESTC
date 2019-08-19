#include "dcmodel.h"
#include <QDebug>
#include <QSerialPort>
#include <windows.h>
#include <QThread>
extern HANDLE hCom1;
extern bool WorkModelNorCal;
DcModel::DcModel()
{
    m_WaveType=DC_FUN;
    m_WaveNo=POSITIVE_DC;
    m_SignalChannelOhm=LOW_OHM;
    m_Amp.Unit=QString("mV");
    m_Amp.Value=0;
}

DcModel::~DcModel()
{

}

bool DcModel::SetWaveNo(uint8_t waveIndex)
{
    m_WaveNo=waveIndex;
    qDebug() << "m_WaveNo: "<< m_WaveNo;
    return true;
}

int DcModel::GetWaveNo()
{
    return m_WaveNo;
}



void DcModel::InitWaveNo(uint8_t waveIndex)
{
    m_WaveNo=waveIndex;
    m_SignalChannelOhm=LOW_OHM;
    m_Amp.Unit=QString("mV");
    m_Amp.Value=20;
    WaveParaSend();
}

bool DcModel::WaveParaSend()
{
    DWORD writeSize;
    QByteArray waveNocontrolWord;
    waveNocontrolWord[0]=0xAB;
    waveNocontrolWord[1]=0x01;
    waveNocontrolWord[2]=0x11;
    waveNocontrolWord[3]=0x00;
    waveNocontrolWord[4]=0x00;
    waveNocontrolWord[5]=0x00;
    waveNocontrolWord[6]=0x01;
    waveNocontrolWord[7]=0xBA;
    QByteArray ohmcontrolWord;
    ohmcontrolWord[0]=0xAB;
    ohmcontrolWord[1]=0x01;
    ohmcontrolWord[2]=0x13;
    ohmcontrolWord[3]=0x00;
    ohmcontrolWord[4]=0x00;
    ohmcontrolWord[5]=0x00;
    ohmcontrolWord[6]=0x01;
    ohmcontrolWord[7]=0xBA;
    switch (m_WaveNo){
    case POSITIVE_DC:
        qDebug() << "切换到正直流";
        waveNocontrolWord[5]=0x01;

        break;
    case NEGATIVE_DC:
        qDebug() << "切换到负直流";
        waveNocontrolWord[5]=0x02;
        break;
    default:
        break;
    }

    switch (m_SignalChannelOhm){
        case LOW_OHM:
            ohmcontrolWord[5]=0x02;
            qDebug() << "切换到50欧阻抗";
            break;
        case HIGH_OHM: 
            ohmcontrolWord[5]=0x01;
            qDebug() << "切换到1M阻抗";
            break;
        default:
            break;
    }

    uint64_t word=GetDcAmpValue(m_Amp);
    uint8_t gear=0;
    if( word < 150000 ){
        gear=1;
    }else if( word < 10000000){
        gear=2;
    }else if(word < 150000000){
        gear=3;
    }
    QByteArray gearControlWord;
    gearControlWord[0]=0xAB;
    gearControlWord[1]=0x01;
    gearControlWord[2]=0x14;
    gearControlWord[3]=0;
    gearControlWord[4]=0;
    gearControlWord[5]=gear;
    gearControlWord[6]=0x01;
    gearControlWord[7]=0xBA;

    uint32_t sendword=0;
    sendword=AmpFreqConverToControlWord(word);
    QByteArray AmpControlWord;
    AmpControlWord[0]=0xAB;
    AmpControlWord[1]=0x01;
    AmpControlWord[2]=0x12;
    AmpControlWord[3]=(sendword >> 16) & 0xff;
    AmpControlWord[4]=(sendword >> 8 ) & 0xff;
    AmpControlWord[5]=(sendword) & 0xff;
    AmpControlWord[6]=0x01;
    AmpControlWord[7]=0xBA;

    QByteArray OutControlWord;
    if(WorkModelNorCal){
        OutControlWord[0]=0xAB;
        OutControlWord[1]=0x01;
        OutControlWord[2]=0x14;
        OutControlWord[3]=0;
        OutControlWord[4]=0;
        OutControlWord[5]=0;
        OutControlWord[6]=0x01;
        OutControlWord[7]=0xBA;
    }else{
        OutControlWord[0]=0xAB;
        OutControlWord[1]=0x02;
        OutControlWord[2]=0x15;
        OutControlWord[3]=0;
        OutControlWord[4]=0;
        OutControlWord[5]=0;
        OutControlWord[6]=0x02;
        OutControlWord[7]=0xBA;
    }

    WriteFile(hCom1,waveNocontrolWord,8,&writeSize,NULL);
    QThread::msleep(50);
    WriteFile(hCom1,ohmcontrolWord,8,&writeSize,NULL);
    QThread::msleep(50);

    WriteFile(hCom1,AmpControlWord,8,&writeSize,NULL);
    QThread::msleep(50);
    WriteFile(hCom1,OutControlWord,8,&writeSize,NULL);
    QThread::msleep(50);
    return true;
}

void DcModel::WaveInit()
{
    InitWaveNo(POSITIVE_DC);
    return;
}

bool DcModel::SetSignalChannelOhm(int ohm)
{
    m_SignalChannelOhm=ohm;
    return true;
}

int DcModel::GetSignalChannelOhm()
{
    return m_SignalChannelOhm;
}

void DcModel::SetWaveAmp(Para val)
{
    m_Amp=val;
}

Para DcModel::GetWaveAmp()
{
    return m_Amp;
}

void DcModel::Open()
{
    qDebug() << "打开直流模块";
}

void DcModel::Close()
{
    qDebug() << "关闭直流模块";
    DWORD writeSize;
    uint8_t Data[8]={0xAB,0x01,0x15,0x00,0x00,0x00,0x01,0xBA};
    WriteFile(hCom1,Data,8,&writeSize,NULL);
}
