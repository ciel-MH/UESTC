#include "rescapmeasurementdialog.h"
#include "ui_rescapmeasurementdialog.h"
#include <QDebug>
#include <QSerialPort>
#include <QHash>
#include <windows.h>
extern HANDLE hCom1;

ResCapMeasurementDialog::ResCapMeasurementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResCapMeasurementDialog)
{
    ui->setupUi(this);
    currentMeasurementType=1;
    InitDialogUi();
    isRunning=false;
    connect(&measureModel,SIGNAL(showResMeasureText(QString)),\
            this,SLOT(updateMeasureDataSlot(QString)));
    connect(&measureModel,SIGNAL(showCapMeasureText(QString)),\
            this,SLOT(updateMeasureDataSlot(QString)));

    ui->OutputOn_pushBtn->setText(QString("开始测量"));
    ui->StandBy_pushBtn->setText(QString("停止测量"));
}

ResCapMeasurementDialog::~ResCapMeasurementDialog()
{

    delete ui;
}

void ResCapMeasurementDialog::StopResCapMeasure()
{
    if(isRunning){
      measureModel.stopMeasure();
      isRunning=false;
    }
}

void ResCapMeasurementDialog::initCap()
{
   // measureModel.initMeasureCap();
}

void ResCapMeasurementDialog::on_OutputOn_pushBtn_clicked()
{
     measureModel.startMeasure();
     isRunning=true;
}

void ResCapMeasurementDialog::on_StandBy_pushBtn_clicked()
{
    StopResCapMeasure();
}

void ResCapMeasurementDialog::updateMeasureDataSlot(QString text)
{
    ui->label->setText(text);
}


void ResCapMeasurementDialog::InitDialogUi()
{
    ui->ResCap_WaveNo_Label->setText(QString("测量类型"));
    QStringList typeList;
    typeList << QString("电阻测量") << QString("电容测量");
    ui->ResCap_WaveNo_Cmb->addItems(typeList);
    ui->ResCap_WaveNo_Cmb->setCurrentIndex(0);
    ui->init_cap_pushbutton->setText(QString("初始化电容"));
}


void ResCapMeasurementDialog::on_ResCap_WaveNo_Cmb_currentIndexChanged(int index)
{
    currentMeasurementType=index+1;
    measureModel.setMeasureType(currentMeasurementType);
    if(index){
        ui->init_cap_pushbutton->show();
    }else{
        ui->init_cap_pushbutton->hide();
    }
}

void ResCapMeasurementDialog::on_init_cap_pushbutton_clicked()
{
    measureModel.initMeasureCap();
}
