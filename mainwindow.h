#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dcdialog.h>
#include <edgedialog.h>
#include <sindialog.h>
#include <squdialog.h>
#include <markerdialog.h>
#include <overloadpulsedialog.h>
#include <pulsewidthdialog.h>
#include <funwavedialog.h>
#include <videotrigerdialog.h>
#include <rescapmeasurementdialog.h>
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_DcDialog_Btn_clicked();

    void on_SquDialog_Btn_clicked();

    void on_SinDialog_Btn_clicked();

    void on_EdgeDialog_Btn_clicked();

    void on_FunWaveDialog_Btn_clicked();

    void on_PulseWidthDialog_Btn_clicked();

    void on_OverPulseDialog_Btn_clicked();

    void on_ResMearDialog_Btn_clicked();

    void on_VedioTriggerDialog_Btn_clicked();

    void on_MarkerDialog_Btn_clicked();

    void serialport_open(QAction *);
    void switch_cal_nor(QAction *);
    void shutdown();
private:
    Ui::MainWindow *ui;
    InterfaceModel *pInterfaceModel;
    DcDialog *pDcDialog;
    SquDialog *pSquDialog;
    MarkerDialog *pMarkerDialog;
    EdgeDialog *pEdgeDialog;
    OverloadPulseDialog *pOverloadPulseDialog;
    SinDialog *pSinDialog;
    FunWaveDialog *pFunWaveDialog;
    PulseWidthDialog *pPulseWidthDialog;
    VideoTrigerDialog *pVideoTrigerDialog;
    ResCapMeasurementDialog *pResCapMeasurementDialog;
};

#endif // MAINWINDOW_H
