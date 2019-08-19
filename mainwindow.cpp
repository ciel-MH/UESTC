#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QComboBox>
#include <iostream>
#include <dcdialog.h>
#include <QtSerialPort/qserialportinfo.h>
#include <QtSerialPort/qserialport.h>
#include <QMessageBox>
#include <windows.h>
#include <windows.h>
using namespace std;
QSerialPort port;
HANDLE hCom1;
bool WorkModelNorCal=false;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pInterfaceModel=NULL;
    pDcDialog=NULL;
    pSinDialog=NULL;
    pEdgeDialog=NULL;
    pSquDialog=NULL;
    pOverloadPulseDialog=NULL;
    pPulseWidthDialog=NULL;
    pMarkerDialog=NULL;
    pFunWaveDialog=NULL;
    pVideoTrigerDialog=NULL;
    pResCapMeasurementDialog=NULL;
    ui->DcDialog_Btn->setText(QString("直流"));
    ui->EdgeDialog_Btn->setText(QString("快沿"));
    ui->FunWaveDialog_Btn->setText(QString("函数波形"));
    ui->MarkerDialog_Btn->setText(QString("时标"));
    ui->SquDialog_Btn->setText(QString("方波"));
    ui->SinDialog_Btn->setText(QString("稳幅正弦"));
    ui->OverPulseDialog_Btn->setText(QString("过载脉冲"));
    ui->PulseWidthDialog_Btn->setText(QString("脉宽"));
    ui->ResMearDialog_Btn->setText(QString("阻抗测量"));
    ui->VedioTriggerDialog_Btn->setText(QString("视频触发"));

   // QAction *paction=new QAction(QString("工作模式"),this);
   // ui->menuBar->addAction(paction);
  //  connect(paction,&QAction::triggered,this,&MainWindow::shutdown);

    QMenu *pmenu=new QMenu(QString("选择端口"));
    QActionGroup *group=new QActionGroup(this);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        //这里相当于自动识别串口号之后添加到了cmb，如果要手动选择可以用下面列表的方式添加进去
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            //将串口号添加到pmenu
            QAction *pAction=group->addAction(info.portName());
            pAction->setCheckable(true);
            pmenu->addAction(pAction);
            //关闭串口等待人为(打开串口按钮)打开
            serial.close();
        }
    }
    ui->menuBar->addMenu(pmenu);
    connect(pmenu,&QMenu::triggered,this,&MainWindow::serialport_open);

    QMenu *pWorkMenu=new QMenu(QString("工作模式"));
    QActionGroup *gWorkroup=new QActionGroup(this);
    QAction *pNorAction=gWorkroup->addAction(QString("已校准模式"));
    pNorAction->setCheckable(true);
    pWorkMenu->addAction(pNorAction);
    QAction *pCalAction=gWorkroup->addAction(QString("未校准模式"));
    pCalAction->setCheckable(true);
    pWorkMenu->addAction(pCalAction);

    ui->menuBar->addMenu(pWorkMenu);
    connect(pWorkMenu,&QMenu::triggered,this,&MainWindow::switch_cal_nor);
    ui->mainToolBar->deleteLater();

    ui->DcDialog_Btn->setEnabled(false);
    ui->EdgeDialog_Btn->setEnabled(false);
    ui->FunWaveDialog_Btn->setEnabled(false);
    ui->MarkerDialog_Btn->setEnabled(false);
    ui->OverPulseDialog_Btn->setEnabled(false);
    ui->PulseWidthDialog_Btn->setEnabled(false);
    ui->ResMearDialog_Btn->setEnabled(false);
    ui->SinDialog_Btn->setEnabled(false);
    ui->SquDialog_Btn->setEnabled(false);
    ui->VedioTriggerDialog_Btn->setEnabled(false);
   // showFullScreen();
}

MainWindow::~MainWindow()
{
    if(pInterfaceModel !=NULL){
        delete pInterfaceModel;
        pInterfaceModel=NULL;
    }
    if(pDcDialog !=NULL){
        delete pDcDialog;
        pDcDialog=NULL;
        qDebug() << "delete pDcDialog";
    }
    if(pSquDialog !=NULL){
        delete pSquDialog;
        pSquDialog=NULL;
        qDebug() << "delete pSquDialog";
    }
    if(pSinDialog != NULL){
        delete pSinDialog;
        pSinDialog=NULL;
        qDebug() << "delete pSinDialog";
    }
    if(pEdgeDialog !=NULL){
        delete pEdgeDialog;
        pEdgeDialog=NULL;
        qDebug() << "delete pEdgeDialog";
    }
    if(pOverloadPulseDialog !=NULL){
        delete pOverloadPulseDialog;
        pOverloadPulseDialog=NULL;
        qDebug() << "delete pOverloadPulseDialog";
    }
    if(pMarkerDialog !=NULL ){
        delete pMarkerDialog;
        pMarkerDialog=NULL;
        qDebug() << "delete pMarkerDialog";
    }
    if(pPulseWidthDialog !=NULL){
        delete pPulseWidthDialog;
        pPulseWidthDialog=NULL;
        qDebug() << "delete pPulseWidthDialog";
    }
    if(pFunWaveDialog != NULL){
        delete pFunWaveDialog;
        pFunWaveDialog=NULL;
        qDebug() << "delete pFunWaveDialog";
    }
    if(pVideoTrigerDialog !=NULL){
        delete pVideoTrigerDialog;
        pVideoTrigerDialog=NULL;
        qDebug() << "delete pVideoTrigerDialog";
    }
    if(pResCapMeasurementDialog !=NULL){
        delete pResCapMeasurementDialog;
        pResCapMeasurementDialog=NULL;
    }
    delete ui;
}



void MainWindow::on_DcDialog_Btn_clicked()
{
    if(pDcDialog == NULL){
         pDcDialog=new DcDialog(this);
         pDcDialog->setModal(true);
    }
    pDcDialog->exec();
}

void MainWindow::on_SquDialog_Btn_clicked()
{
    if(pSquDialog == NULL){
        pSquDialog=new SquDialog(this);
        pSquDialog->setModal(true);
    }
    pSquDialog->exec();
}

void MainWindow::on_SinDialog_Btn_clicked()
{
    if(pSinDialog == NULL){
        pSinDialog=new SinDialog(this);
        pSinDialog->setModal(true);
    }
    pSinDialog->exec();
}

void MainWindow::on_EdgeDialog_Btn_clicked()
{
    if(pEdgeDialog == NULL){
        pEdgeDialog=new EdgeDialog(this);
        pEdgeDialog->setModal(true);
    }
    pEdgeDialog->exec();
}

void MainWindow::on_FunWaveDialog_Btn_clicked()
{
    if(pFunWaveDialog == NULL){
        pFunWaveDialog=new FunWaveDialog(this);
        pFunWaveDialog->setModal(true);
    }
    pFunWaveDialog->exec();
}

void MainWindow::on_PulseWidthDialog_Btn_clicked()
{
    if(pPulseWidthDialog == NULL){
        pPulseWidthDialog=new PulseWidthDialog(this);
        pPulseWidthDialog->setModal(true);
    }
    pPulseWidthDialog->exec();
}

void MainWindow::on_OverPulseDialog_Btn_clicked()
{
    if(pOverloadPulseDialog == NULL){
        pOverloadPulseDialog=new OverloadPulseDialog(this);
        pOverloadPulseDialog->setModal(true);
    }
    pOverloadPulseDialog->exec();
}


void MainWindow::on_ResMearDialog_Btn_clicked()
{
//    QString currentPortName=port.portName();
//    port.close();
    if(pResCapMeasurementDialog ==NULL){
        pResCapMeasurementDialog=new ResCapMeasurementDialog(this);
        pResCapMeasurementDialog->setModal(true);
    }
    pResCapMeasurementDialog->exec();
    qDebug() << "Finish";
    pResCapMeasurementDialog->StopResCapMeasure();

//    if(port.isOpen()){
//       port.close();
//    }
//    port.setPortName(currentPortName);
//    if(port.open(QIODevice::ReadWrite)){
//        port.setBaudRate(115200);
//        port.setDataBits(QSerialPort::Data8);
//        port.setParity(QSerialPort::NoParity);
//        port.setFlowControl(QSerialPort::NoFlowControl);
//        port.setStopBits(QSerialPort::OneStop);
//        port.setReadBufferSize(4);
//        port.clearError();
//        port.clear();
//    }else{
//       QMessageBox::warning(this,QString("错误"),QString("串口打开失败,请重新选择端口"));
//       port.close();
//    }
}

void MainWindow::on_VedioTriggerDialog_Btn_clicked()
{
    if(pVideoTrigerDialog == NULL){
        pVideoTrigerDialog=new VideoTrigerDialog(this);
        pVideoTrigerDialog->setModal(true);
    }
    pVideoTrigerDialog->exec();
}

void MainWindow::on_MarkerDialog_Btn_clicked()
{
    if(pMarkerDialog == NULL){
        pMarkerDialog=new MarkerDialog(this);
        pMarkerDialog->setModal(true);
    }
    pMarkerDialog->exec();
}


void MainWindow::serialport_open(QAction *pAction)
{
    /*
    if(port.isOpen()){
        port.close();
        pAction->setChecked(false);
        ui->DcDialog_Btn->setEnabled(false);
        ui->EdgeDialog_Btn->setEnabled(false);
        ui->FunWaveDialog_Btn->setEnabled(false);
        ui->MarkerDialog_Btn->setEnabled(false);
        ui->OverPulseDialog_Btn->setEnabled(false);
        ui->PulseWidthDialog_Btn->setEnabled(false);
        ui->ResMearDialog_Btn->setEnabled(false);
        ui->SinDialog_Btn->setEnabled(false);
        ui->SquDialog_Btn->setEnabled(false);
        return;
    }
    pAction->setCheckable(true);
    port.setPortName(pAction->text());
    if(port.open(QIODevice::ReadWrite)){
        port.setBaudRate(9600);
        port.setDataBits(QSerialPort::Data8);
        port.setParity(QSerialPort::NoParity);
        port.setFlowControl(QSerialPort::NoFlowControl);
        port.setStopBits(QSerialPort::OneStop);
        port.setReadBufferSize(4);
        port.clearError();
        port.clear();

        ui->DcDialog_Btn->setEnabled(true);
        ui->EdgeDialog_Btn->setEnabled(true);
        ui->FunWaveDialog_Btn->setEnabled(true);
        ui->MarkerDialog_Btn->setEnabled(true);
        ui->OverPulseDialog_Btn->setEnabled(true);
        ui->PulseWidthDialog_Btn->setEnabled(true);
        ui->ResMearDialog_Btn->setEnabled(true);
        ui->SinDialog_Btn->setEnabled(true);
        ui->SquDialog_Btn->setEnabled(true);
        ui->VedioTriggerDialog_Btn->setEnabled(true);
    }else{
       QMessageBox::warning(this,QString("错误"),QString("串口打开失败"));
       port.close();
       ui->DcDialog_Btn->setEnabled(false);
       ui->EdgeDialog_Btn->setEnabled(false);
       ui->FunWaveDialog_Btn->setEnabled(false);
       ui->MarkerDialog_Btn->setEnabled(false);
       ui->OverPulseDialog_Btn->setEnabled(false);
       ui->PulseWidthDialog_Btn->setEnabled(false);
       ui->ResMearDialog_Btn->setEnabled(false);
       ui->SinDialog_Btn->setEnabled(false);
       ui->SquDialog_Btn->setEnabled(false);
    }*/

    const char* szStr=pAction->text().toStdString().data();
    WCHAR wszClassName[8];
    memset(wszClassName,0,sizeof(wszClassName));
    MultiByteToWideChar(CP_ACP,0,szStr,strlen(szStr)+1,wszClassName,sizeof(wszClassName)/sizeof(wszClassName[0]));
    hCom1=CreateFile(wszClassName,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
    if(hCom1 == INVALID_HANDLE_VALUE){
           cout << "open serialport false" << endl;
           return;
    }else{
        cout << "open serialport sucess" <<endl;
        ui->DcDialog_Btn->setEnabled(true);
        ui->EdgeDialog_Btn->setEnabled(true);
        ui->FunWaveDialog_Btn->setEnabled(true);
        ui->MarkerDialog_Btn->setEnabled(true);
        ui->OverPulseDialog_Btn->setEnabled(true);
        ui->PulseWidthDialog_Btn->setEnabled(true);
        ui->ResMearDialog_Btn->setEnabled(true);
        ui->SinDialog_Btn->setEnabled(true);
        ui->SquDialog_Btn->setEnabled(true);
        ui->VedioTriggerDialog_Btn->setEnabled(true);
    }
    SetupComm(hCom1,8,4);
    COMMTIMEOUTS TimeOuts;
    TimeOuts.ReadIntervalTimeout=100;
    TimeOuts.ReadTotalTimeoutConstant=5000;
    TimeOuts.ReadTotalTimeoutMultiplier=5000;
    TimeOuts.WriteTotalTimeoutConstant=2000;
    TimeOuts.WriteTotalTimeoutMultiplier=500;
    SetCommTimeouts(hCom1,&TimeOuts);
    DCB dcb;
    GetCommState(hCom1,&dcb);
    dcb.BaudRate=115200;
    dcb.ByteSize=8;
    dcb.Parity=NOPARITY;
    dcb.StopBits=ONESTOPBIT;
    SetCommState(hCom1,&dcb);
}

void MainWindow::switch_cal_nor(QAction *paction)
{
    if(QString("已校准模式") == paction->text()){
        WorkModelNorCal=true;
    }else if(QString("未校准模式") == paction->text()){
        WorkModelNorCal=false;
    }
    qDebug() << WorkModelNorCal;
}

void MainWindow::shutdown()
{
    qDebug() << "shutdown";
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
           return;
         //获取关机特权的LUID
         LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,    &tkp.Privileges[0].Luid);
         tkp.PrivilegeCount = 1;
         tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

         //获取这个进程的关机特权
         AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
         if(GetLastError() != ERROR_SUCCESS) return;

         // 强制关闭计算机
         if ( !ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0))
              return;

}
