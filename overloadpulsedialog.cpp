#include "overloadpulsedialog.h"
#include "ui_overloadpulsedialog.h"

OverloadPulseDialog::OverloadPulseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OverloadPulseDialog)
{
    ui->setupUi(this);
    pOverloadPulseModel=new OverloadPulseModel();
    InitDialogUi();
}

OverloadPulseDialog::~OverloadPulseDialog()
{
    delete pOverloadPulseModel;
    pOverloadPulseModel=NULL;
    delete ui;
}

void OverloadPulseDialog::InitDialogUi()
{
    ui->OverPulseAmp_Label->setText(QString("标准幅度:"));
    ui->OverPulseDuration_Label->setText(QString("脉冲宽度:"));
    ui->OverPulseEnergy_Label->setText(QString("脉冲能量:"));
    ui->OverPulsePower_Label->setText(QString("信号功率:"));

    ui->OverPulseDurationUnit_Label->setText(QString("S"));
    ui->OverPulseAmpUnit_Label->setText(QString("V"));
    ui->OverPulseEnergyUnit_Label->setText(QString("J"));
    ui->OverPulsePowerUnit_Label->setText(QString("W"));

    connect(ui->OverPulseAmp_Dsb,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,&OverloadPulseDialog::OverPulseAmp_Dsb_valueChanged);
    connect(ui->OverPulseEnergy_Dsb,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,&OverloadPulseDialog::OverPulseEnergy_Dsb_valueChanged);

    ui->OutputOn_pushBtn->setText(QString("输出开"));
    ui->StandBy_pushBtn->setText(QString("输出关"));
}

void OverloadPulseDialog::OverPulseAmp_Dsb_valueChanged(double val)
{
    Para temp=pOverloadPulseModel->GetWaveAmp();
    temp.Value=val;
    pOverloadPulseModel->SetWaveAmp(temp);
}

void OverloadPulseDialog::OverPulseEnergy_Dsb_valueChanged(double val)
{
    Para temp=pOverloadPulseModel->GetEnergePara();
    temp.Value=val;
    pOverloadPulseModel->SetEnergePara(temp);
}

void OverloadPulseDialog::on_StandBy_pushBtn_clicked()
{
    ui->StandBy_pushBtn->setEnabled(false);
    pOverloadPulseModel->Close();
}

void OverloadPulseDialog::on_OutputOn_pushBtn_clicked()
{
    if(!ui->StandBy_pushBtn->isEnabled()){
        ui->StandBy_pushBtn->setEnabled(true);
    }
    pOverloadPulseModel->WaveParaSend();
}

void OverloadPulseDialog::on_OverPulseDuration_Dsb_valueChanged(double val)
{
    Para temp=pOverloadPulseModel->GetDurationPara();
    temp.Value=val;
    pOverloadPulseModel->SetDurationPara(temp);
}
