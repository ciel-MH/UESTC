#include "sindialog.h"
#include "ui_sindialog.h"

SinDialog::SinDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SinDialog)
{
    ui->setupUi(this);
    pSinModel=new SinModel();
    InitDialogUi();
}

SinDialog::~SinDialog()
{
    delete pSinModel;
    delete ui;
}

void SinDialog::InitDialogUi()
{

    QStringList AmpUnitList;
    AmpUnitList << QString("uVpk-pk") << QString("mVpk-pk") << QString("Vpk-pk");
    ui->SinAmpUnit_Cmb->addItems(AmpUnitList);
    QStringList FreqUnitList;
    FreqUnitList << QString("Hz") << QString("kHz") << QString("MHz") << QString("GHz");
    ui->SinFreqUnit_Cmb->addItems(FreqUnitList);
    ui->SinAmpUnit_Cmb->setCurrentIndex(1);
    ui->SinAmp_Dial->setRange(0,10);
    ui->SinAmp_Dsb->setRange(0,10);
    ui->SinFreqUnit_Cmb->setCurrentIndex(1);
    ui->SinFreq_Dial->setRange(0,1000);
    ui->SinFreq_Dsb->setRange(0,1000);
  //  connect(ui->SinAmp_Dial,&QDial::valueChanged,ui->SinAmp_Dsb,&QDoubleSpinBox::setValue);
    connect(ui->SinAmp_Dsb,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&SinDialog::SinAmp_Dsb_valueChanged);
    connect(ui->SinAmpUnit_Cmb,static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(SinDialog::*)(const QString &)>(&SinDialog::SinAmpUnit_Cmb_currentIndexChanged));
    connect(ui->SinAmpUnit_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(SinDialog::*)(int)>(&SinDialog::SinAmpUnit_Cmb_currentIndexChanged));

    connect(ui->SinFreq_Dsb,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&SinDialog::SinFreq_Dsb_valueChanged);
    connect(ui->SinFreqUnit_Cmb,static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(SinDialog::*)(const QString &)>(&SinDialog::SinFreqUnit_Cmb_currentIndexChanged));
  //  connect(ui->SinFreq_Dial,&QDial::valueChanged,ui->SinFreq_Dsb,&QDoubleSpinBox::setValue);
    connect(ui->SinFreqUnit_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(SinDialog::*)(int)>(&SinDialog::SinFreqUnit_Cmb_currentIndexChanged));
    ui->OutputOn_pushBtn->setText(QString("输出开"));
    ui->StandBy_pushBtn->setText(QString("输出关"));
}

void SinDialog::SinAmp_Dsb_valueChanged(double val)
{
    Para temp=pSinModel->GetWaveAmp();
    temp.Value=val;
    pSinModel->SetWaveAmp(temp);
    ui->lcdNumber->display(QString::number(val));
}

void SinDialog::SinAmpUnit_Cmb_currentIndexChanged(const QString &text)
{
    Para temp=pSinModel->GetWaveAmp();
    temp.Unit=text;
    pSinModel->SetWaveAmp(temp);
}

void SinDialog::SinAmpUnit_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->SinAmp_Dsb->setRange(0,1000);
        ui->SinAmp_Dial->setRange(0,1000);
        break;
    case 1:
        ui->SinAmp_Dsb->setRange(0,1000);
        ui->SinAmp_Dial->setRange(0,1000);
        break;
    case 2:
        ui->SinAmp_Dial->setRange(0,10);
        ui->SinAmp_Dsb->setRange(0,10);
        break;
    default:
        break;
    }
}

void SinDialog::SinFreq_Dsb_valueChanged(double freq)
{
    Para temp=pSinModel->GetFrequencePara();
    temp.Value=freq;
    pSinModel->SetFrequencePara(temp);
}

void SinDialog::SinFreqUnit_Cmb_currentIndexChanged(const QString &text)
{
    Para temp=pSinModel->GetFrequencePara();
    temp.Unit=text;
    pSinModel->SetFrequencePara(temp);
}

void SinDialog::SinFreqUnit_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->SinFreq_Dsb->setRange(0,1000);
        ui->SinFreq_Dial->setRange(0,1000);
        break;
    case 1:
        ui->SinFreq_Dsb->setRange(0,1000);
        ui->SinFreq_Dial->setRange(0,1000);
        break;
    case 2:
        ui->SinFreq_Dsb->setRange(0,1000);
        ui->SinFreq_Dial->setRange(0,1000);
        break;
    case 3:
        ui->SinFreq_Dsb->setRange(0,6);
        ui->SinFreq_Dial->setRange(0,6);
        break;
    default:
        break;
    }
}

void SinDialog::on_StandBy_pushBtn_clicked()
{
    ui->StandBy_pushBtn->setEnabled(false);
    pSinModel->Close();
}

void SinDialog::on_OutputOn_pushBtn_clicked()
{
    if(!ui->StandBy_pushBtn->isEnabled()){
        ui->StandBy_pushBtn->setEnabled(true);
    }
    pSinModel->WaveParaSend();
}
