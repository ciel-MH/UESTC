#ifndef PULSEWIDTHMODEL_H
#define PULSEWIDTHMODEL_H

#include <interfacemodel.h>
class PulseWidthModel : public InterfaceModel
{
public:
    PulseWidthModel();
    virtual ~PulseWidthModel();
private:
    uint8_t m_WaveNo;//波形下的具体子波形
    Para m_GearPara;
    int m_GearMultiplyValue;
    Para m_Amp;
    Para m_Frequence;
    Para m_PulsePeriodPara;
    int  m_SignalChannelOhm;
public:
     bool  SetWaveNo(uint8_t waveIndex);//选择在子波形
     int   GetWaveNo();
     void  InitWaveNo(uint8_t waveIndex);
     bool  WaveParaSend();//完成
     void  WaveInit();
     bool  SetSignalChannelOhm(int);
     int   GetSignalChannelOhm(void);
     bool  SetFrequencePara(Para);
     Para  GetFrequencePara(void);
     void  SetWaveAmp(Para val);
     Para  GetWaveAmp(void);
     void  Open(void);
     void  Close(void);
//脉宽模块特有功能
public:
     bool SetPulsePeriodPara(Para);
     Para GetPulsePeriodPara(void);

};

#endif // PULSEWIDTHMODEL_H
