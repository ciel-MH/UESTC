#ifndef EDGEDIALOG_H
#define EDGEDIALOG_H

#include <QDialog>
#include <edgemodel.h>
namespace Ui {
class EdgeDialog;
}

class EdgeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EdgeDialog(QWidget *parent = 0);
    ~EdgeDialog();

private:
    Ui::EdgeDialog *ui;
    EdgeModel *pEdgeModel;
private:
    void InitDialogUi(void);
private slots:

    void EdgeWaveNo_Cmb_currentIndexChanged(int);
    void EdgeAmp_Dsb_valueChanged(double);
    void EdgeAmpUnit_Cmb_currentIndexChanged(const QString&text);
    void EdgeAmpUnit_Cmb_currentIndexChanged(int index);
    void EdgeFreq_Dsb_valueChanged(double);
    void EdgeFreqUnit_Cmb_currentIndexChanged(const QString&);
    void EdgeFreqUnit_Cmb_currentIndexChanged(int index);
    void EdgeUpDown_Cmb_currentIndexChanged(int index);
    void on_StandBy_pushBtn_clicked();
    void on_OutputOn_pushBtn_clicked();
};

#endif // EDGEDIALOG_H
