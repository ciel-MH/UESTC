#ifndef RESCAPMEASUREMENTDIALOG_H
#define RESCAPMEASUREMENTDIALOG_H
#include <rescapmeasurementmodel.h>
#include <QDialog>
#include "rescapmeasurementmodel.h"
namespace Ui {
class ResCapMeasurementDialog;
}


class ResCapMeasurementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResCapMeasurementDialog(QWidget *parent = 0);
    ~ResCapMeasurementDialog();
    void StopResCapMeasure(void);
    void initCap(void);
private slots:
    void on_OutputOn_pushBtn_clicked();

    void on_StandBy_pushBtn_clicked();

    void updateMeasureDataSlot(QString text);

    void on_ResCap_WaveNo_Cmb_currentIndexChanged(int index);

    void on_init_cap_pushbutton_clicked();

private:
    Ui::ResCapMeasurementDialog *ui;
    bool isRunning;
private:
    void InitDialogUi(void);
    MeasureModel measureModel;
    uint8_t currentMeasurementType;
};

#endif // RESCAPMEASUREMENTDIALOG_H
