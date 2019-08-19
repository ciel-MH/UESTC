#ifndef SQUDIALOG_H
#define SQUDIALOG_H

#include <QDialog>
#include <squmodel.h>
namespace Ui {
class SquDialog;
}

class SquDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SquDialog(QWidget *parent = 0);
    ~SquDialog();

private:
    Ui::SquDialog *ui;
    SquModel *pSquModel;
private slots:
    void SquWaveNo_Cmb_currentIndexChanged(int);
    void SquAmp_Dsb_valueChanged(double);
    void SquAmpUnit_Cmb_currentIndexChanged(const QString&);
    void SquAmpUnit_Cmb_currentIndexChanged(int index);
    void SquFreq_Dsb_valueChanged(double);
    void SquFreqUnit_Cmb_currentIndexChanged(const QString&);
    void SquFreqUnit_Cmb_currentIndexChanged(int index);
    void SquOhm_Cmb_currentIndexChanged(int index);
    void on_StandBy_pushBtn_clicked();
    void on_OutputOn_pushBtn_clicked();

private:
    void InitDialogUi(void);
};

#endif // SQUDIALOG_H
