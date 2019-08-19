#ifndef INTERFACEMODEL_H
#define INTERFACEMODEL_H
#include <QtSerialPort/qserialport.h>
#include <QString>
#include <QDebug>
#define LOAD_CAL_ON 1

extern QSerialPort port;
typedef enum WaveForm
{
    DC_FUN=0,//直流
    SQUARE_FUN,//方波
    SINUSOID_FUN,//正弦
    EDGE_FUN,//快沿
    MARKER_FUN,//时标
    FUNWAVE_FUN, //函数波
    OVERLOADPULSE_FUN, //过载脉冲
    PWIDTH_FUN,  //脉宽信号
    OHMCAPMEAR_FUN, //电阻电容测试
    TELEVISION_FUN//视频触发
}WaveFormType;
//脉宽
#define  PULSE_WIDTH                  1
//过载脉冲
#define  OVERLOAD_PULSE               1
//方波
#define  POSITIVE_SQUARE              1                   //正方波
#define	 NEGATIVE_SQUARE              2                  //负方波
#define  SYMMETRICAL_SQUARE           3                 //对称方波
//直流
#define  POSITIVE_DC                  1                   //正直流
#define  NEGATIVE_DC                  2                   //负直流
//函数波
#define  FUNWAVE_SQUARE               1
#define  FUNWAVE_SIN                  2
#define  FUNWAVE_TRIANGULAR           3                   //三角波
#define  FUNWAVE_SAWTOOTH             4                   //
//正弦
#define  SINGLECHANNEL                1
//快沿
#define  Edge_Rising                  true
#define  Edge_Falling                 false
#define  Edge_500ps                   1
#define  Edge_150ps                   2                    //150ps快沿上升沿
#define  Edge_500ps_Down              3
#define  Edge_150ps_Down              4                    //150ps快沿下降沿
//时标
#define  MARKER_SQUARE                1
#define  MARKER_PLUS                  2
#define  MARKER_TRIANGULAR            3
#define  MARKER_SIN                   4
//阻抗
#define  LOW_OHM              2
#define  HIGH_OHM             1
//电阻电容测量
#define  Res_Measurement      0
#define  Cap_Measurement      1

#define TV_BRIGHTLEVEL_WHITE 1
#define TV_BRIGHTLEVEL_GRAY  2
#define TV_BRIGHTLEVEL_BLACK 3

#define TV_POLARITY_POS 1
#define TV_POLARITY_NEG 2

#define TV_SYNC_625 1
#define TV_SYNC_525 2
struct Para
{
    double Value;
    QString Unit;
};

struct WavePara{
    Para Amp;
    Para Freq;
};

struct ParaRange{
    double min;
    double max;
    QString min_uint;
    QString max_uint;
};

class InterfaceModel
{
public:
    InterfaceModel();
    virtual ~InterfaceModel();

    virtual bool FreParaToPeriodPara(void);//周期更新
    virtual bool PeriodParaToFrePara(void);
    bool FrequencyValueAndUnitProcess(Para& );
    bool PeriodValueAndUnitProcess(Para& );
    bool AmpValueAndUnitProcess(Para& );
    uint32_t AmpFreqConverToControlWord(uint64_t temp);
    uint64_t GetDcAmpValue(Para);
    uint64_t GetFreqValue(Para);
    uint64_t GetAmpValue(Para);
    uint64_t GetPeriodParaValue(Para);
public:
    static int  m_WaveType;
    static int  m_TriggerRate;                  //触发速率
public:
    bool   SetWaveType(int type);          //设置波形类型,取值应为WaveForm里的值
    int    GetWaveType(void);                  //获取波形


/*以下为子模块需要实现的函数*/
public:
    virtual bool  SetWaveNo(uint8_t waveIndex);		//各种波形类型下的，具体波形编号
    virtual int   GetWaveNo();					//各种波形类型下的，具体波形编号
    virtual bool  WaveParaSend();
    virtual void  WaveInit();
    virtual bool  SetSignalChannelOhm(int);
    virtual int   GetSignalChannelOhm(void);
    virtual bool  SetFrequencePara(Para);
    virtual Para  GetFrequencePara(void);
    virtual void  SetWaveAmp(Para);
    virtual Para  GetWaveAmp(void);
    virtual void  Open(void);
    virtual void  Close(void);
};

#endif // INTERFACEMODEL_H
