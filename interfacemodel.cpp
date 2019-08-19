#include "interfacemodel.h"
#include <QtMath>
#include <QHash>
#include <QDebug>
#include <windows.h>
int InterfaceModel::m_WaveType=SQUARE_FUN;
int  InterfaceModel::m_TriggerRate=0;
InterfaceModel::InterfaceModel()
{

}

InterfaceModel::~InterfaceModel()
{

}

bool InterfaceModel::FreParaToPeriodPara(void)
{
    return true;
}

bool InterfaceModel::PeriodParaToFrePara(void)
{
    return true;
}

bool InterfaceModel::FrequencyValueAndUnitProcess(Para &FrePara) //将频率转换到合适的单位和数值
{
    if ( 0 >=FrePara.Value )
    {
        return false;
    }
    if ( FrePara.Value >= 1000.0 )
    {
            if ( QString("Hz") == FrePara.Unit )//字符串直接比较
            {
                FrePara.Value=FrePara.Value/1000;
                FrePara.Unit = QString("kHz");
            }
            else if ( QString("kHz")  == FrePara.Unit)
            {
                FrePara.Value=FrePara.Value/1000;
                FrePara.Unit = QString("MHz");
            }
            else if (  QString("MHz") == FrePara.Unit )
            {
                FrePara.Value=FrePara.Value/1000;
                FrePara.Unit= QString("GHz");
            }
    }
    if (FrePara.Value < 1.0 )
    {
       if(QString("THz")==FrePara.Unit )
       {
                FrePara.Value=FrePara.Value*1000;
                FrePara.Unit = QString("GHz");
       }
       else if (QString("GHz")==FrePara.Unit )
       {
                FrePara.Value=FrePara.Value*1000;
                FrePara.Unit = QString("MHz");
       }
       else if ( QString("MHz")== FrePara.Unit  )
       {
                FrePara.Value=FrePara.Value*1000;
                FrePara.Unit = QString("kHz");
       }
       else if (  QString("kHz")==FrePara.Unit  )
       {
                FrePara.Value=FrePara.Value*1000;
                FrePara.Unit = QString("Hz");
       }
    }
        return true;
}

bool InterfaceModel::PeriodValueAndUnitProcess(Para &periodPara)
{
    if( 0 >= periodPara.Value )
    {
            return 0;
    }
    if ( periodPara.Value >= 1000.0 )
    {
            if ( QString("ps") == periodPara.Unit )
            {
                periodPara.Value=periodPara.Value/1000;
                periodPara.Unit = QString("ns");
            }
            else if ( QString("ns") == periodPara.Unit )
            {
                periodPara.Value=periodPara.Value/1000;
                periodPara.Unit = QString("us");
            }
            else if ( QString("us") ==periodPara.Unit)
            {
                periodPara.Value=periodPara.Value/1000;
                periodPara.Unit = QString("ms");
            }
            else if ( QString("ms") ==periodPara.Unit )
            {
                periodPara.Value=periodPara.Value/1000;
                periodPara.Unit= QString("s");
            }
     }
        if (periodPara.Value <1.0 )
        {
            if (QString("s")==periodPara.Unit )
            {
                periodPara.Value=periodPara.Value*1000;
                periodPara.Unit = QString("ms");
            }
            else if (QString("ms")== periodPara.Unit  )
            {
                periodPara.Value=periodPara.Value*1000;
                periodPara.Unit = QString("us");
            }
            else if ( QString("us")==periodPara.Unit  )
            {
                periodPara.Value=periodPara.Value*1000;
                periodPara.Unit = QString("ns");
            }
            else if ( QString("ns")==periodPara.Unit  )
            {
                periodPara.Value=periodPara.Value*1000;
                periodPara.Unit = QString("ps");
            }
        }
        return true;
}

bool InterfaceModel::AmpValueAndUnitProcess(Para &standAmpPara)
{
    if (m_WaveType == DC_FUN)//直流波形时，单位表示方式特殊
        {
            if ( 0 >=standAmpPara.Value )
            {
                return false;
            }
            if ( standAmpPara.Value>=1000.0 )
            {
                if ( QString("uV") == standAmpPara.Unit )
                {
                    standAmpPara.Value=standAmpPara.Value/1000;
                    standAmpPara.Unit = QString("mV");
                }
                else if (  QString("mV")  ==standAmpPara.Unit)
                {
                    standAmpPara.Value=standAmpPara.Value/1000;
                    standAmpPara.Unit = QString("V");
                }
                else if (  QString("V") ==standAmpPara.Unit )
                {
                    standAmpPara.Unit= QString("V");
                }
            }
            if ( qFabs(standAmpPara.Value) <1.0 )//求长整型的绝对值
            {
                if (QString("V")==standAmpPara.Unit )
                {
                    standAmpPara.Value=standAmpPara.Value*1000;
                    standAmpPara.Unit = QString("mV");
                }
                else if ( QString("mV")== standAmpPara.Unit  )
                {
                    standAmpPara.Value=standAmpPara.Value*1000;
                    standAmpPara.Unit = QString("uV");
                }
                else if ( QString("uV")==standAmpPara.Unit  )
                {
                    standAmpPara.Unit = QString("uV");
                }
            }
            return true;
        }
    else
        {
            if ( 0 >=standAmpPara.Value )
            {
                return false;
            }
            if ( standAmpPara.Value>=1000.0 )
            {
                if ( QString("uVpk-pk") == standAmpPara.Unit )
                {
                    standAmpPara.Value=standAmpPara.Value/1000;
                    standAmpPara.Unit = QString("mVpk-pk");
                }
                else if (  QString("mVpk-pk")  ==standAmpPara.Unit)
                {
                    standAmpPara.Value=standAmpPara.Value/1000;
                    standAmpPara.Unit = QString("Vpk-pk");
                }
                else if (  QString("Vpk-pk") ==standAmpPara.Unit )
                {
                    standAmpPara.Unit= QString("Vpk-pk");
                }
            }
            if ( qFabs(standAmpPara.Value) <1.0 )
            {
                if (QString("Vpk-pk")==standAmpPara.Unit )
                {
                    standAmpPara.Value=standAmpPara.Value*1000;
                    standAmpPara.Unit = QString("mVpk-pk");
                }
                else if ( QString("mVpk-pk")== standAmpPara.Unit  )
                {
                    standAmpPara.Value=standAmpPara.Value*1000;
                    standAmpPara.Unit = QString("uVpk-pk");
                }
                else if (  QString("uVpk-pk")==standAmpPara.Unit  )
                {
                    standAmpPara.Unit = QString("uVpk-pk");
                }
            }
            return true;

    }
}

uint32_t InterfaceModel::AmpFreqConverToControlWord(uint64_t temp)
{
    uint8_t n=0;
    uint32_t reval;
    while (temp > 0xFFFFF){
        temp=temp/10;
        n++;
    }
    reval= (n << 20) | temp;
    return reval;
}

uint64_t InterfaceModel::GetDcAmpValue(Para para) //单位uV
{
    QHash<QString,int> hash;
    hash[QString("mV")]=1000;
    hash[QString("V")]=1000000;
    return hash[para.Unit]*para.Value;
}

uint64_t InterfaceModel::GetFreqValue(Para para) //单位mHZ
{
    QHash<QString,int> hash;
    hash[QString("Hz")]=1;
    hash[QString("kHz")]=1000;
    hash[QString("MHz")]=1000000;
    hash[QString("GHz")]=1000000000;
    return hash[para.Unit]*para.Value*1000;
}

uint64_t InterfaceModel::GetAmpValue(Para para) //单位uV
{
    QHash<QString,double> hash;
    hash[QString("uVpk-pk")]=1;
    hash[QString("mVpk-pk")]=1000;
    hash[QString("Vpk-pk")]=1000000;
    return hash[para.Unit]*para.Value;
}

uint64_t InterfaceModel::GetPeriodParaValue(Para para) //单位ps
{
    QHash<QString,double> hash;
    hash[QString("ps")]=1;
    hash[QString("ns")]=1000;
    hash[QString("us")]=1000000;
    hash[QString("ms")]=1000000000;
    hash[QString("s")] =1000000000000;
    return hash[para.Unit]*para.Value;
}

bool InterfaceModel::SetWaveType(int type)
{
    m_WaveType = type;
    qDebug() << "切换到对应的波形";
    return true;
}

int InterfaceModel::GetWaveType(void)
{
    return m_WaveType;
}

bool InterfaceModel::SetWaveNo(uint8_t waveIndex)
{
    return true;
}

int InterfaceModel::GetWaveNo()
{
    return 0;
}

bool InterfaceModel::WaveParaSend()
{
 return true;
}

void InterfaceModel::WaveInit()
{
    return;
}

bool InterfaceModel::SetSignalChannelOhm(int)
{
    return true;
}

int InterfaceModel::GetSignalChannelOhm(void)
{
    return 0;
}

bool InterfaceModel::SetFrequencePara(Para)
{
    return true;
}

Para InterfaceModel::GetFrequencePara()
{
    Para amp;
    amp.Unit=QString("");
    amp.Value=0;
    return amp;
}

void InterfaceModel::SetWaveAmp(Para)
{
    return;
}

Para InterfaceModel::GetWaveAmp()
{
    Para para;
    para.Unit=QString("");
    para.Value=0;
    return para;
}

void InterfaceModel::Open()
{

}

void InterfaceModel::Close()
{

}


