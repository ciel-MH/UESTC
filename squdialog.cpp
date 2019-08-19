#include "squdialog.h"
#include "ui_squdialog.h"

SquDialog::SquDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SquDialog)
{
    ui->setupUi(this);
    pSquModel=new SquModel();
    InitDialogUi();
}

SquDialog::~SquDialog()
{
    delete pSquModel;
    delete ui;
}



void SquDialog::SquWaveNo_Cmb_currentIndexChanged(int Index)
{
    switch (Index) {
    case 0:
        pSquModel->SetWaveNo(POSITIVE_SQUARE);
        break;
    case 1:
        pSquModel->SetWaveNo(NEGATIVE_SQUARE);
        break;
    case 2:
        pSquModel->SetWaveNo(SYMMETRICAL_SQUARE);
        break;
    default:
        break;
    }
}

void SquDialog::SquAmp_Dsb_valueChanged(double val)
{
    Para temp=pSquModel->GetWaveAmp();
    temp.Value=val;
    pSquModel->SetWaveAmp(temp);
    ui->lcdNumber->display(QString::number(val));
}

void SquDialog::SquAmpUnit_Cmb_currentIndexChanged(const QString &text)
{
    Para temp=pSquModel->GetWaveAmp();
    temp.Unit=text;
    pSquModel->SetWaveAmp(temp);
}

void SquDialog::SquAmpUnit_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->SquAmp_Dsb->setRange(0,1000);
        ui->SquAmp_Dial->setRange(0,1000);
        break;
    case 1:
        ui->SquAmp_Dsb->setRange(0,1000);
        ui->SquAmp_Dial->setRange(0,1000);
        break;
    case 2:
        if(ui->SquOhm_Cmb->currentIndex() == 1){
            ui->SquAmp_Dial->setRange(0,7);
            ui->SquAmp_Dsb->setRange(0,7);
        }else{
            ui->SquAmp_Dial->setRange(0,150);
            ui->SquAmp_Dsb->setRange(0,150);
        }
        break;
    default:
        break;
    }
}

void SquDialog::SquFreq_Dsb_valueChanged(double val)
{
    Para temp=pSquModel->GetFrequencePara();
    temp.Value=val;
    pSquModel->SetFrequencePara(temp);
}

void SquDialog::SquFreqUnit_Cmb_currentIndexChanged(const QString &text)
{
    Para temp=pSquModel->GetFrequencePara();
    temp.Unit=text;
    pSquModel->SetFrequencePara(temp);
}

void SquDialog::SquFreqUnit_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->SquFreq_Dsb->setRange(0,1000);
        ui->SquFreq_Dial->setRange(0,1000);
        break;
    case 1:
        ui->SquFreq_Dsb->setRange(0,100);
        ui->SquFreq_Dial->setRange(0,100);
        break;
    case 2:
        ui->SquFreq_Dsb->setRange(0,1);
        ui->SquFreq_Dial->setRange(0,1);
        break;
    case 3:
        ui->SquFreq_Dsb->setRange(0,1);
        ui->SquFreq_Dial->setRange(0,1);
        break;
    default:
        break;
    }
}

void SquDialog::SquOhm_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        pSquModel->SetSignalChannelOhm(HIGH_OHM);
        if(ui->SquAmpUnit_Cmb->currentIndex() == 2){
            ui->SquAmp_Dsb->setRange(0,160);
            ui->SquAmp_Dial->setRange(0,160);
        }
        break;
    case 1:
        pSquModel->SetSignalChannelOhm(LOW_OHM);
        if(ui->SquAmpUnit_Cmb->currentIndex() == 2){
            ui->SquAmp_Dsb->setRange(0,7);
            ui->SquAmp_Dial->setRange(0,7);
        }
        break;
    default:
        break;
    }
}

void SquDialog::InitDialogUi()
{
    QStringList SquOhmList;
    SquOhmList << QString(" 1M  Ω ") << QString(" 50   Ω ");
    ui->SquOhm_Cmb->addItems(SquOhmList);
    QStringList WaveNoList;
    WaveNoList << QString("正方波") << QString("负方波") << QString("对称方波");
    ui->SquWaveNo_Cmb->addItems(WaveNoList);
    QStringList AmpUnitList;
    AmpUnitList << QString("uVpk-pk") << QString("mVpk-pk") << QString("Vpk-pk");
    ui->SquAmpUnit_Cmb->addItems(AmpUnitList);
    QStringList FreqUnitList;
    FreqUnitList << QString("Hz") << QString("kHz") << QString("MHz") << QString("GHz");
    ui->SquFreqUnit_Cmb->addItems(FreqUnitList);
    ui->SquAmpUnit_Cmb->setCurrentIndex(2);

    ui->SquFreqUnit_Cmb->setCurrentIndex(1);
    ui->SquAmp_Dsb->setRange(0,7);
    ui->SquAmp_Dial->setRange(0,7);
    ui->SquFreq_Dsb->setRange(0,1000);
    ui->SquFreq_Dial->setRange(0,1000);
    ui->SquOhm_Cmb->setCurrentIndex(1);

    connect(ui->SquWaveNo_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&SquDialog::SquWaveNo_Cmb_currentIndexChanged);

    connect(ui->SquAmp_Dsb,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&SquDialog::SquAmp_Dsb_valueChanged);
    connect(ui->SquAmpUnit_Cmb,static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(SquDialog::*)(const QString &)>(&SquDialog::SquAmpUnit_Cmb_currentIndexChanged));
   // connect(ui->SquAmp_Dial,&QDial::valueChanged,ui->SquAmp_Dsb,&QDoubleSpinBox::setValue);
    connect(ui->SquAmpUnit_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(SquDialog::*)(int)>(&SquDialog::SquAmpUnit_Cmb_currentIndexChanged));

    connect(ui->SquFreq_Dsb,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&SquDialog::SquFreq_Dsb_valueChanged);
    connect(ui->SquFreqUnit_Cmb,static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(SquDialog::*)(const QString &)>(&SquDialog::SquFreqUnit_Cmb_currentIndexChanged));
  //  connect(ui->SquFreq_Dial,&QDial::valueChanged,ui->SquFreq_Dsb,&QDoubleSpinBox::setValue);
    connect(ui->SquFreqUnit_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(SquDialog::*)(int)>(&SquDialog::SquFreqUnit_Cmb_currentIndexChanged));
    connect(ui->SquOhm_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(SquDialog::*)(int)>(&SquDialog::SquOhm_Cmb_currentIndexChanged));
    ui->OutputOn_pushBtn->setText(QString("输出开"));
    ui->StandBy_pushBtn->setText(QString("输出关"));
}

void SquDialog::on_StandBy_pushBtn_clicked()
{
    ui->StandBy_pushBtn->setEnabled(false);
    pSquModel->Close();
}

void SquDialog::on_OutputOn_pushBtn_clicked()
{
    if(!ui->StandBy_pushBtn->isEnabled()){
        ui->StandBy_pushBtn->setEnabled(true);
    }
    pSquModel->WaveParaSend();
}
