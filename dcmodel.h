#ifndef DCMODEL_H
#define DCMODEL_H
#include "interfacemodel.h"

class DcModel : public InterfaceModel
{
public:
    DcModel();
    virtual ~DcModel();
private:
    uint8_t m_WaveNo;//直流波形下的具体子波形
    Para m_GearPara;
    int m_GearMultiplyValue;
    Para m_Amp;
    int  m_SignalChannelOhm;
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
     void  Open(void);
     void  Close(void);
};

#endif // DCMODEL_H
