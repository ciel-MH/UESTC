#ifndef SINMODEL_H
#define SINMODEL_H

#include <interfacemodel.h>
class SinModel : public InterfaceModel
{
public:
    SinModel();
    virtual ~SinModel();
private:
    uint8_t m_WaveNo;//正弦波形下的具体子波形
    Para m_GearPara;
    int  m_GearMultiplyValue;
    Para m_Amp;
    Para m_Frequence;
    int  m_SignalChannelOhm;
public:
     bool  SetWaveNo(uint8_t waveIndex);//选择在子波形
     int   GetWaveNo();
     void  InitWaveNo(uint8_t waveIndex);
     bool  WaveParaSend();
     void  WaveInit();
     bool  SetSignalChannelOhm(int);
     int   GetSignalChannelOhm(void);
     bool  SetFrequencePara(Para);
     Para  GetFrequencePara(void);

     void  SetWaveAmp(Para val);
     Para  GetWaveAmp(void);

     void  Open(void);
     void  Close(void);
};

#endif // SINMODEL_H
