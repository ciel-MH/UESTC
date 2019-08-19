#ifndef MARKERMODEL_H
#define MARKERMODEL_H
#include <interfacemodel.h>

class MarkerModel : public InterfaceModel
{
public:
    MarkerModel();
    virtual ~MarkerModel();
private:
    uint8_t m_WaveNo;//直流波形下的具体子波形
    Para m_GearPara;
    int m_GearMultiplyValue;
    Para m_Amp;
    Para m_Frequence;
    Para m_PeriodPara;
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
     bool  FreParaToPeriodPara(void);
     bool  PeriodParaToFrePara(void);
public://时标模块特有功能
     bool  SetPeriodPara(Para);
     Para  GetPeriodPara(void);
     void  Open(void);
     void  Close(void);
};

#endif // MARKERMODEL_H
