#ifndef OVERLOADPULSEMODEL_H
#define OVERLOADPULSEMODEL_H

#include <interfacemodel.h>
class OverloadPulseModel:public InterfaceModel
{
public:
    OverloadPulseModel();
    virtual ~OverloadPulseModel();
private:
    uint8_t m_WaveNo;//直流波形下的具体子波形
    Para m_GearPara;
    int m_GearMultiplyValue;
    Para m_Amp;
    int  m_SignalChannelOhm;
    Para m_EnergyPara;
    Para m_PowerPara;
    Para m_DurationPara;
public:
     bool  SetWaveNo(uint8_t waveIndex);//选择在子波形
     int   GetWaveNo();
     void  InitWaveNo(uint8_t waveIndex);
     bool  WaveParaSend();//完成
     void  WaveInit();
     bool  SetSignalChannelOhm(int);
     int   GetSignalChannelOhm(void);
     void  SetWaveAmp(Para val);
     Para  GetWaveAmp(void);
//过载脉冲模块特有功能
public:
     void  SetEnergePara(Para);
     Para  GetEnergePara(void);
     void  SetPowerPara(Para);
     Para  GetPowerPara();
     void  SetDurationPara(Para);
     Para  GetDurationPara(void);
     void  Open(void);
     void  Close(void);
};

#endif // OVERLOADPULSEMODEL_H
