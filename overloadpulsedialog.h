#ifndef OVERLOADPULSEDIALOG_H
#define OVERLOADPULSEDIALOG_H

#include <QDialog>
#include <overloadpulsemodel.h>
namespace Ui {
class OverloadPulseDialog;
}

class OverloadPulseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OverloadPulseDialog(QWidget *parent = 0);
    ~OverloadPulseDialog();

private:
    Ui::OverloadPulseDialog *ui;
    OverloadPulseModel *pOverloadPulseModel;
private:
    void InitDialogUi(void);
private slots:
    void OverPulseAmp_Dsb_valueChanged(double);
    void OverPulseEnergy_Dsb_valueChanged(double);
    void on_StandBy_pushBtn_clicked();
    void on_OutputOn_pushBtn_clicked();
    void on_OverPulseDuration_Dsb_valueChanged(double arg1);
};

#endif // OVERLOADPULSEDIALOG_H
