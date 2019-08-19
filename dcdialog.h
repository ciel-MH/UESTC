#ifndef DCDIALOG_H
#define DCDIALOG_H

#include <QDialog>
#include <dcmodel.h>

namespace Ui {
class DcDialog;
}

class DcDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DcDialog(QWidget *parent = 0);
    ~DcDialog();

private:
    Ui::DcDialog *ui;
    DcModel     *pDcModel;
private slots:

    void DcWaveNo_Cmb_currentIndexChanged(int);
    void DcAmp_Dsb_valueChanged(double);
    void DcAmpUnit_Cmb_currentIndexChanged(const QString&);
    void DcAmpUnit_Cmb_currentIndexChanged(int index);
    void DcOhm_Cmb_currentIndexChanged(int index);
    void on_StandBy_pushBtn_clicked();
    void on_OutputOn_pushBtn_clicked();

private:
    void InitDialogUi(void);
};

#endif // DCDIALOG_H
