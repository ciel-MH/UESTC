#include "pulsewidthdialog.h"
#include "ui_pulsewidthdialog.h"

PulseWidthDialog::PulseWidthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PulseWidthDialog)
{
    ui->setupUi(this);
    pPulseWidthModel=new PulseWidthModel();
    InitDialogUi();
}

PulseWidthDialog::~PulseWidthDialog()
{
    delete pPulseWidthModel;
    delete ui;
}

void PulseWidthDialog::InitDialogUi()
{

    ui->PulseWidthAmp_Label->setText(QString("输出幅度:"));
    ui->PulseWidthFreq_Label->setText(QString("信号频率:"));
    ui->PulseWidthPeriodPara_Label->setText(QString("脉冲宽度:"));
    ui->PulseWidthPeriodParaUnit_Label->setText(QString("ns"));
    QStringList AmpUnitList;
    AmpUnitList << QString("uVpk-pk") << QString("mVpk-pk") << QString("Vpk-pk");
    ui->PulseWidthAmpUnit_Cmb->addItems(AmpUnitList);
    QStringList FreqUnitList;
    FreqUnitList << QString("Hz") << QString("kHz") << QString("MHz");
    ui->PulseWidthFreqUnit_Cmb->addItems(FreqUnitList);

    connect(ui->PulseWidthAmp_Dsb,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&PulseWidthDialog::PulseWidthAmp_Dsb_valueChanged);
    connect(ui->PulseWidthAmpUnit_Cmb,static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(PulseWidthDialog::*)(const QString &)>(&PulseWidthDialog::PulseWidthAmpUnit_Cmb_currentIndexChanged));
   // connect(ui->PulseWidthAmp_Dial,&QDial::valueChanged,ui->PulseWidthAmp_Dsb,&QDoubleSpinBox::setValue);
    connect(ui->PulseWidthAmpUnit_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(PulseWidthDialog::*)(int)>(&PulseWidthDialog::PulseWidthAmpUnit_Cmb_currentIndexChanged));

    connect(ui->PulseWidthFreq_Dsb,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&PulseWidthDialog::PulseWidthFreq_Dsb_valueChanged);
    connect(ui->PulseWidthFreqUnit_Cmb,static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(PulseWidthDialog::*)(const QString &)>(&PulseWidthDialog::PulseWidthFreqUnit_Cmb_currentIndexChanged));
  //  connect(ui->PulseWidthFreq_Dial,&QDial::valueChanged,ui->PulseWidthFreq_Dsb,&QDoubleSpinBox::setValue);
    connect(ui->PulseWidthFreqUnit_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(PulseWidthDialog::*)(int)>(&PulseWidthDialog::PulseWidthFreqUnit_Cmb_currentIndexChanged));

    connect(ui->PulseWidthPeriodPara_Dsb,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,&PulseWidthDialog::PulseWidthPeriodPara_Dsb_valueChanged);
   // connect(ui->PulseWidthPeriodPara_Dial,&QDial::valueChanged,ui->PulseWidthPeriodPara_Dsb,&QDoubleSpinBox::setValue);

    ui->PulseWidthAmpUnit_Cmb->setCurrentIndex(0);
    ui->PulseWidthAmp_Dsb->setValue(0);
    ui->PulseWidthFreqUnit_Cmb->setCurrentIndex(0);
    ui->PulseWidthFreq_Dsb->setValue(0);
    ui->OutputOn_pushBtn->setText(QString("输出开"));
    ui->StandBy_pushBtn->setText(QString("输出关"));
}

void PulseWidthDialog::PulseWidthFreq_Dsb_valueChanged(double freq)
{
    Para temp=pPulseWidthModel->GetFrequencePara();
    temp.Value=freq;
    pPulseWidthModel->SetFrequencePara(temp);
}

void PulseWidthDialog::PulseWidthPeriodPara_Dsb_valueChanged(double period)
{
    Para temp=pPulseWidthModel->GetPulsePeriodPara();
    temp.Value=period;
    pPulseWidthModel->SetPulsePeriodPara(temp);
}

void PulseWidthDialog::PulseWidthAmp_Dsb_valueChanged(double amp)
{
    Para temp=pPulseWidthModel->GetWaveAmp();
    temp.Value=amp;
    pPulseWidthModel->SetWaveAmp(temp);
    ui->lcdNumber->display(QString::number(amp));
}

void PulseWidthDialog::PulseWidthAmpUnit_Cmb_currentIndexChanged(const QString &unit)
{
    Para temp=pPulseWidthModel->GetWaveAmp();
    temp.Unit=unit;
    pPulseWidthModel->SetWaveAmp(temp);
}

void PulseWidthDialog::PulseWidthAmpUnit_Cmb_currentIndexChanged(int index)
{

}

void PulseWidthDialog::PulseWidthFreqUnit_Cmb_currentIndexChanged(const QString &unit)
{
    Para temp=pPulseWidthModel->GetWaveAmp();
    temp.Unit=unit;
    pPulseWidthModel->SetFrequencePara(temp);
}

void PulseWidthDialog::PulseWidthFreqUnit_Cmb_currentIndexChanged(int index)
{

}

void PulseWidthDialog::on_StandBy_pushBtn_clicked()
{
    ui->StandBy_pushBtn->setEnabled(false);
 //   ui->PulseWidthAmp_Dsb->setValue(0);
  //  ui->PulseWidthFreq_Dsb->setValue(0);
 //   ui->PulseWidthPeriodPara_Dsb->setValue(0);
    pPulseWidthModel->Close();
}

void PulseWidthDialog::on_OutputOn_pushBtn_clicked()
{
    if(!ui->StandBy_pushBtn->isEnabled()){
        ui->StandBy_pushBtn->setEnabled(true);
    }
    pPulseWidthModel->WaveParaSend();
}
