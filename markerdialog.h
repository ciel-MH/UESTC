#ifndef MARKERDIALOG_H
#define MARKERDIALOG_H

#include <QDialog>
#include <markermodel.h>
namespace Ui {
class MarkerDialog;
}

class MarkerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MarkerDialog(QWidget *parent = 0);
    ~MarkerDialog();

private:
    Ui::MarkerDialog *ui;
    MarkerModel *pMarkerModel;
private:
    void InitDialogUi(void);

private slots:
    void MarkerWaveNo_Cmb_currentIndexChanged(int);
    void MarkerWaveAmp_Cmb_valueChanged(int);
    void MarkerPeriod_Dsb_valueChanged(double);
    void MarkerPeriodUnit_Cmb_currentIndexChanged(const QString&);
    void MarkerPeriodUnit_Cmb_currentIndexChanged(int index);

    void on_StandBy_pushBtn_clicked();
    void on_OutputOn_pushBtn_clicked();
};

#endif // MARKERDIALOG_H
