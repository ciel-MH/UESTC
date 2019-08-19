#ifndef FUNWAVEDIALOG_H
#define FUNWAVEDIALOG_H

#include <QDialog>
#include <funwavemodel.h>
namespace Ui {
class FunWaveDialog;
}

class FunWaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FunWaveDialog(QWidget *parent = 0);
    ~FunWaveDialog();

private:
    Ui::FunWaveDialog *ui;
    FunWaveModel *pFunWaveModel;
private:
    void InitDialogUi(void);
private slots:
    void FunWaveOhm_Cmb_currentIndexChanged(int);
    void FunWaveNo_Cmb_currentIndexChanged(int);
    void FunWaveAmp_Dsb_valueChanged(double);
    void FunWaveAmpUnit_Cmb_currentIndexChanged(const QString&);
    void FunWaveAmpUnit_Cmb_currentIndexChanged(int index);
    void FunWaveFreq_Dsb_valueChanged(double);
    void FunWaveFreqUnit_Cmb_currentIndexChanged(const QString&);
    void FunWaveFreqUnit_Cmb_currentIndexChanged(int index);
    void on_StandBy_pushBtn_clicked();
    void on_OutputOn_pushBtn_clicked();
};

#endif // FUNWAVEDIALOG_H
