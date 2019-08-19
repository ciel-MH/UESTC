#ifndef SINDIALOG_H
#define SINDIALOG_H

#include <QDialog>
#include <sinmodel.h>
namespace Ui {
class SinDialog;
}

class SinDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SinDialog(QWidget *parent = 0);
    ~SinDialog();

private:
    Ui::SinDialog *ui;
    SinModel *pSinModel;
private:
    void InitDialogUi(void);
private slots:
    void SinAmp_Dsb_valueChanged(double);
    void SinAmpUnit_Cmb_currentIndexChanged(const QString&);
    void SinAmpUnit_Cmb_currentIndexChanged(int index);
    void SinFreq_Dsb_valueChanged(double);
    void SinFreqUnit_Cmb_currentIndexChanged(const QString&);
    void SinFreqUnit_Cmb_currentIndexChanged(int index);
    void on_StandBy_pushBtn_clicked();
    void on_OutputOn_pushBtn_clicked();
};

#endif // SINDIALOG_H
