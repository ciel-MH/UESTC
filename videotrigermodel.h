#ifndef VIDEOTRIGERMODEL_H
#define VIDEOTRIGERMODEL_H
#include "interfacemodel.h"

class VideoTrigerModel : public InterfaceModel
{
public:
    VideoTrigerModel();
    virtual ~VideoTrigerModel();
private:
    uint8_t m_Polarity;
    uint8_t m_BrightLevel;
    uint8_t m_Sync;
public:
    void SetPolarity(uint8_t polarity);
    void SetBrightLevel(uint8_t brightlevel);
    void SetSync(uint8_t sync);
    bool WaveParaSend();
    void WaveInit();
    void open(void);
    void close(void);
};

#endif // VIDEOTRIGERMODEL_H
