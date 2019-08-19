#ifndef EDGEMODEL_H
#define EDGEMODEL_H
#include <interfacemodel.h>

class EdgeModel : public InterfaceModel
{
public:
    EdgeModel();
    virtual ~EdgeModel();
private:
    uint8_t m_WaveNo;//快沿波形下的具体子波形
    Para m_GearPara;
    int  m_GearMultiplyValue;
    Para m_Amp;
    Para m_Frequence;
    int  m_SignalChannelOhm;
    bool m_RisingFallingFlag; //上升下降标志,0上升沿,1下降沿
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
     void  SetRisingFallingFlag(bool);
     bool  GetRisingFallingFlag(void);
     void  SetWaveAmp(Para val);
     Para  GetWaveAmp(void);

     void  Open(void);
     void  Close(void);
};

#endif // EDGEMODEL_H
