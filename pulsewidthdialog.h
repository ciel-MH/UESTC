#ifndef PULSEWIDTHDIALOG_H
#define PULSEWIDTHDIALOG_H

#include <QDialog>
#include <pulsewidthmodel.h>
namespace Ui {
class PulseWidthDialog;
}

class PulseWidthDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PulseWidthDialog(QWidget *parent = 0);
    ~PulseWidthDialog();

private slots:
    void on_StandBy_pushBtn_clicked();

    void on_OutputOn_pushBtn_clicked();

private:
    Ui::PulseWidthDialog *ui;
    PulseWidthModel *pPulseWidthModel;
private:
    void InitDialogUi(void);
private slots:
    void PulseWidthFreq_Dsb_valueChanged(double);
    void PulseWidthPeriodPara_Dsb_valueChanged(double);
    void PulseWidthAmp_Dsb_valueChanged(double);
    void PulseWidthAmpUnit_Cmb_currentIndexChanged(const QString&);
    void PulseWidthAmpUnit_Cmb_currentIndexChanged(int index);
    void PulseWidthFreqUnit_Cmb_currentIndexChanged(const QString&);
    void PulseWidthFreqUnit_Cmb_currentIndexChanged(int index);
};

#endif // PULSEWIDTHDIALOG_H
